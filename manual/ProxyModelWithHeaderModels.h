#ifndef PROXY_MODEL_WITH_HEADER_MODELS
#define PROXY_MODEL_WITH_HEADER_MODELS

#include <QProxyModel>
#include <QPointer>
#include "HierarchicalHeaderView.h"

class ProxyModelWithHeaderModels: public QProxyModel
{
		Q_OBJECT

		QPointer<QAbstractItemModel> _horizontalHeaderModel;
		QPointer<QAbstractItemModel> _verticalHeaderModel;
	public:
		ProxyModelWithHeaderModels(QObject* parent=0);

		QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const;

		void setHorizontalHeaderModel(QAbstractItemModel* model);

		void setVerticalHeaderModel(QAbstractItemModel* model);
};

#endif
