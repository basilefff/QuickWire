#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <pipewire/pipewire.h>
#include "pipewiremodel.h"

int main(int argc, char *argv[])
{
	pw_init(&argc, &argv);
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
					 &app, []() { QCoreApplication::exit(-1); },
	Qt::QueuedConnection);
	engine.loadFromModule("QuickWire", "Main");

	qDebug() << "Let's test the debug tools";

	return app.exec();
}
