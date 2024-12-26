#include "TableModel.h"

TableModel::TableModel(Watchlist& watchlist, QObject* parent) : watchlist{ watchlist }, QAbstractTableModel{ parent }
{
}

TableModel::~TableModel()
{
}

int TableModel::rowCount(const QModelIndex& parent) const
{
	return this->watchlist.getTutorials().size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	std::vector<Tutorial> tutorials = this->watchlist.getTutorials();
	Tutorial currentTutorial = tutorials[row];

	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(currentTutorial.getTitle());
		case 1:
			return QString::fromStdString(currentTutorial.getPresenter());
		case 2:
			return QString::fromStdString(std::to_string(currentTutorial.getDuration().getMinutes()) + ":" + std::to_string(currentTutorial.getDuration().getSeconds()));
		case 3:
			return QString::fromStdString(std::to_string(currentTutorial.getLikes()));
		default:
			break;
		}
	}

	return QVariant{};
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Title" };
			case 1:
				return QString{ "Presenter" };
			case 2:
				return QString{ "Duration" };
			case 3:
				return QString{ "Likes" };
			default:
				break;
			}
		}
	}

	return QVariant{};
}