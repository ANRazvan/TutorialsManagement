#pragma once
#include <qabstractitemmodel.h>
#include "Watchlist.h"

class TableModel: public QAbstractTableModel
{
private:
	Watchlist& watchlist;

public:
	TableModel(Watchlist& watchlist, QObject* parent = NULL);
	~TableModel();

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	//bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	//Qt::ItemFlags flags(const QModelIndex& index) const override;
	//void update();
};

