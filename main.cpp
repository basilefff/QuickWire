#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
					 &app, []() { QCoreApplication::exit(-1); },
	Qt::QueuedConnection);
	engine.loadFromModule("QuickWire", "Main");

	qDebug() << "Let's test the debug tools\n";

	return app.exec();
}
