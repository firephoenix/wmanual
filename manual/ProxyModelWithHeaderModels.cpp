#include "ProxyModelWithHeaderModels.h"

ProxyModelWithHeaderModels::ProxyModelWithHeaderModels(QObject* parent)
	: QProxyModel(parent)
{}

QVariant ProxyModelWithHeaderModels::data(const QModelIndex& index, int role) const
{
	if(_horizontalHeaderModel && role==HierarchicalHeaderView::HorizontalHeaderDataRole)
	{
		QVariant v;
		v.setValue((QObject*)_horizontalHeaderModel.data());
		return v;
	}
	if(_verticalHeaderModel && role==HierarchicalHeaderView::VerticalHeaderDataRole)
	{
		QVariant v;
		v.setValue((QObject*)_verticalHeaderModel.data());
		return v;
	}
	return QProxyModel::data(index, role);
}

void ProxyModelWithHeaderModels::setHorizontalHeaderModel(QAbstractItemModel* headerModel)
{
	_horizontalHeaderModel=headerModel;
	int cnt=model()->columnCount();
	if(cnt)
		emit headerDataChanged(Qt::Horizontal, 0, cnt-1);
}

void ProxyModelWithHeaderModels::setVerticalHeaderModel(QAbstractItemModel* headerModel)
{
	_verticalHeaderModel=headerModel;
	int cnt=model()->rowCount();
	if(cnt)
		emit headerDataChanged(Qt::Vertical, 0, cnt-1);
}
