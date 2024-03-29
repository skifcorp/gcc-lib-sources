#include "../include/precompiled.h"

#include "../include/main_dlg.h"

#include "../../qxService/include/service/server_infos.h"

#include <QxMemLeak.h>

void main_dlg::init()
{
   setupUi(this);

   QObject::connect(btnStartStop, SIGNAL(clicked()), this, SLOT(onClickStartStop()));
   QObject::connect(cboSerializationType, SIGNAL(currentIndexChanged(int)), this, SLOT(onCboIndexChanged(int)));

   cboSerializationType->addItem("0- serialization_binary", QVariant((int)qx::service::QxConnect::serialization_binary));
   cboSerializationType->addItem("1- serialization_xml", QVariant((int)qx::service::QxConnect::serialization_xml));
   cboSerializationType->addItem("2- serialization_text", QVariant((int)qx::service::QxConnect::serialization_text));
   cboSerializationType->addItem("3- serialization_portable_binary", QVariant((int)qx::service::QxConnect::serialization_portable_binary));
   cboSerializationType->addItem("4- serialization_wide_binary", QVariant((int)qx::service::QxConnect::serialization_wide_binary));
   cboSerializationType->addItem("5- serialization_wide_xml", QVariant((int)qx::service::QxConnect::serialization_wide_xml));
   cboSerializationType->addItem("6- serialization_wide_text", QVariant((int)qx::service::QxConnect::serialization_wide_text));
   cboSerializationType->addItem("7- serialization_polymorphic_binary", QVariant((int)qx::service::QxConnect::serialization_polymorphic_binary));
   cboSerializationType->addItem("8- serialization_polymorphic_xml", QVariant((int)qx::service::QxConnect::serialization_polymorphic_xml));
   cboSerializationType->addItem("9- serialization_polymorphic_text", QVariant((int)qx::service::QxConnect::serialization_polymorphic_text));
   cboSerializationType->setCurrentIndex(cboSerializationType->findData(QVariant((int)qx::service::QxConnect::getSingleton()->getSerializationType())));

   spinPortNumber->setValue(7694);
   spinThreadCount->setValue(qx::service::QxConnect::getSingleton()->getThreadCount());
   onServerIsRunning(false, NULL);
   onClickStartStop();
}

void main_dlg::loadServices()
{
   // Required to be sure to load all services dll : create a dummy service for each dll
   // It is also possible to create a 'plugin system' to load services
   server_infos dummy_01; Q_UNUSED(dummy_01);
}

void main_dlg::onClickStartStop()
{
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
   if (m_pThreadPool)
   {
      m_pThreadPool->disconnect();
      m_pThreadPool.reset();
      txtError->setPlainText("");
      txtTransaction->setPlainText("");
      onServerIsRunning(false, NULL);
   }
   else
   {
      qx::service::QxConnect::getSingleton()->setPort(spinPortNumber->value());
      qx::service::QxConnect::getSingleton()->setThreadCount(spinThreadCount->value());
      qx::service::QxConnect::getSingleton()->setSerializationType((qx::service::QxConnect::serialization_type)(cboSerializationType->itemData(cboSerializationType->currentIndex()).toInt()));
      qx::service::QxConnect::getSingleton()->setCompressData(chkCompressData->isChecked());
      qx::service::QxConnect::getSingleton()->setEncryptData(chkEncryptData->isChecked());

      m_pThreadPool.reset(new qx::service::QxThreadPool());
      QObject::connect(m_pThreadPool.get(), SIGNAL(error(const QString &, qx::service::QxTransaction_ptr)), this, SLOT(onError(const QString &, qx::service::QxTransaction_ptr)));
      QObject::connect(m_pThreadPool.get(), SIGNAL(serverIsRunning(bool, qx::service::QxServer *)), this, SLOT(onServerIsRunning(bool, qx::service::QxServer *)));
      QObject::connect(m_pThreadPool.get(), SIGNAL(transactionFinished(qx::service::QxTransaction_ptr)), this, SLOT(onTransactionFinished(qx::service::QxTransaction_ptr)));
      m_pThreadPool->start();
   }
   QApplication::restoreOverrideCursor();
}

void main_dlg::onCboIndexChanged(int index)
{
   if (index < 0) { cboSerializationType->setToolTip(""); }
   else { cboSerializationType->setToolTip(cboSerializationType->itemText(cboSerializationType->currentIndex())); }
}

void main_dlg::onServerIsRunning(bool bIsRunning, qx::service::QxServer * pServer)
{
   Q_UNUSED(pServer);
   imgIsRunning->setText("");
   imgIsRunning->setPixmap(bIsRunning ? QPixmap(":/run") : QPixmap(":/stop"));
   btnStartStop->setText(bIsRunning ? "Stop Server" : "Start Server");

   spinPortNumber->setEnabled(! bIsRunning);
   spinThreadCount->setEnabled(! bIsRunning);
   cboSerializationType->setEnabled(! bIsRunning);
   chkCompressData->setEnabled(! bIsRunning);
   chkEncryptData->setEnabled(! bIsRunning);
}

void main_dlg::onError(const QString & err, qx::service::QxTransaction_ptr transaction)
{
   if (err.isEmpty()) { txtError->setPlainText(""); return; }
   QString errText = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm") + " : " + err;
   if (transaction) { errText += QString("\r\n\r\n") + qx::serialization::xml::to_string(* transaction); }
   txtError->setPlainText(errText.replace("\t", "    "));
}

void main_dlg::onTransactionFinished(qx::service::QxTransaction_ptr transaction)
{
   if (! transaction) { txtTransaction->setPlainText(""); return; }
   QString text = qx::serialization::xml::to_string(* transaction);
   txtTransaction->setPlainText(text.replace("\t", "    "));
}
