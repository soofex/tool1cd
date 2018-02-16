#ifndef TABLESLISTMODEL_H
#define TABLESLISTMODEL_H

#include <Class_1CD.h>
#include <QAbstractItemModel>

class TablesListModel : public QAbstractItemModel
{
public:
	TablesListModel(T_1CD *db)
	    : db(db) {}

	int rowCount(const QModelIndex &parent) const override
	{
		return db->get_numtables();
	}

	int columnCount(const QModelIndex &parent) const override
	{
		return 7;
	}

	QModelIndex index(int row, int column, const QModelIndex &parent) const override
	{
		return QAbstractItemModel::createIndex(row, column);
	}

	QModelIndex parent(const QModelIndex &child) const override
	{
		return QModelIndex();
	}

	static int object_size(/*const */v8object *file)
	{
		if (file == nullptr) {
			return 0;
		}
		return file->getlen();
	}

	static QString human_size(size_t size_in_bytes)
	{
		size_t modified_size = size_in_bytes;
		QVector<QString> suffix = {tr("B"), tr("KiB"), tr("MiB"), tr("GiB"), tr("TiB")};
		size_t frac_part = 0;
		int suffix_index = 0;
		while (suffix_index < suffix.size() && modified_size > 1000) {
			size_t new_value = modified_size >> 10;
			frac_part = modified_size - (new_value << 10);
			suffix_index++;
			modified_size = new_value;
		}
		qreal value = modified_size + frac_part / 1024.0f;
		return QString::number(value, 'f', 2) + QString(" ") + suffix[suffix_index];
	}

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
	{
		if (!index.isValid()) {
			return QVariant();
		}
		if (role == Qt::DisplayRole) {
			Table *t = db->gettable(index.row());
			switch (index.column()) {
			case 0:
				return QVariant::fromValue(QString::fromStdString(
				                               static_cast<std::string>(t->getname())));

			case 1:
				return QVariant::fromValue(t->get_recordlen());

			case 2:
				return QVariant::fromValue(t->get_recordlock() ? QString("YES") : QString("NO"));

			case 3:
				return human_size(object_size(t->get_file_data()));
			case 4:
				return human_size(object_size(t->get_file_blob()));
			case 5:
				return human_size(object_size(t->get_file_index()));
			case 6:
				return human_size(object_size(t->get_file_data())
				                + object_size(t->get_file_blob())
				                + object_size(t->get_file_index()));
			} // switch
		} else if (role == Qt::TextAlignmentRole) {
			switch (index.column()) {
			case 1:
			case 3:
			case 4:
			case 5:
			case 6:
				return Qt::AlignRight + Qt::AlignVCenter;
			}
		}

		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override
	{
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
			switch (section) {
			case 0:
				return tr("Таблица");
			case 1:
				return tr("Длина записи");
			case 2:
				return tr("RECORDLOCK");
			case 3:
				return tr("Размер файла данных");
			case 4:
				return tr("Размер файла BLOB");
			case 5:
				return tr("Размер файла индексов");
			case 6:
				return tr("Суммарный размер");
			}
		}
		return QVariant();
	}

	T_1CD *db;
};

#endif // TABLESLISTMODEL_H
