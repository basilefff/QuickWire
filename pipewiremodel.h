#ifndef PIPEWIREMODEL_H
#define PIPEWIREMODEL_H

#include <QAbstractListModel>

class PipeWireModel : public QAbstractListModel
{
	Q_OBJECT

public:
	explicit PipeWireModel(QObject *parent = nullptr);

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
	QList<QString> nodes;
};

#endif // PIPEWIREMODEL_H
