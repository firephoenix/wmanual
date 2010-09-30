/*
Copyright (c) 2009, Krasnoshchekov Petr
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY Krasnoshchekov Petr ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL Krasnoshchekov Petr BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
