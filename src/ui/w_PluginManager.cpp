#include "w_PluginManager.hpp"

#include "components/plugins/QvPluginHost.hpp"

PluginManageWindow::PluginManageWindow(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    for (auto &plugin : PluginHost->AvailablePlugins())
    {
        auto item = new QListWidgetItem(pluginListWidget);
        item->setCheckState(Qt::CheckState::Unchecked);
        item->setData(Qt::UserRole, PluginHost->GetPluginInfo(plugin).pluginInterface->InternalName());
        item->setText(PluginHost->GetPluginInfo(plugin).pluginInterface->Name());
        pluginListWidget->addItem(item);
    }
}

PluginManageWindow::~PluginManageWindow()
{
}

void PluginManageWindow::on_pluginListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous)
    auto &info = PluginHost->GetPluginInfo(current->data(Qt::UserRole).toString());
    if (info.pluginInterface != nullptr)
    {
        pluginIconLabel->setPixmap(info.pluginInterface->Icon().pixmap(pluginIconLabel->size() * devicePixelRatio()));
        //
        pluginNameLabel->setText(info.pluginInterface->Name());
        pluginAuthorLabel->setText(info.pluginInterface->Author());
        pluginDescriptionLabel->setText(info.pluginInterface->Description());
        pluginLibPathLabel->setText(info.libraryPath);
        pluginStateLabel->setText(info.isLoaded ? tr("Loaded") : tr("Not loaded"));
        pluginTypeLabel->setText("No impl");
        pluginHookTypeLabel->setText("No impl");
        pluginErrMessageTxt->setPlainText(info.errorMessage.isEmpty() ? "OK" : info.errorMessage);
    }
}

void PluginManageWindow::on_pluginListWidget_itemClicked(QListWidgetItem *item)
{
    on_pluginListWidget_currentItemChanged(item, nullptr);
}
