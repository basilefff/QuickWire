#include "pipewiremodel.h"
#include <pipewire/pipewire.h>

/* [roundtrip] */
struct roundtrip_data {
        int pending;
        struct pw_main_loop *loop;
};

static void on_core_done(void *data, uint32_t id, int seq)
{
        auto *d = (roundtrip_data *)data;

        if (id == PW_ID_CORE && seq == d->pending)
                pw_main_loop_quit(d->loop);
}

static void registry_event_global(void *data, uint32_t id,
                uint32_t permissions, const char *type, uint32_t version,
                const struct spa_dict *props)
{
	auto *nodes = (QList<QString>*)data;
	nodes->append(QString("object: id:%1 type:%2/%3\n").arg(id).arg(type).arg(version));
}

static const struct pw_registry_events registry_events = {
        .version = PW_VERSION_REGISTRY_EVENTS,
        .global = registry_event_global,
};

PipeWireModel::PipeWireModel(QObject *parent)
	: QAbstractListModel(parent)
{
	struct pw_main_loop *loop;
	struct pw_context *context;
	struct pw_core *core;
	struct pw_registry *registry;
	struct spa_hook registry_listener;


	loop = pw_main_loop_new(NULL /* properties */);
	context = pw_context_new(pw_main_loop_get_loop(loop),
							 NULL /* properties */,
							 0 /* user_data size */);

	core = pw_context_connect(context,
							  NULL /* properties */,
							  0 /* user_data size */);

	registry = pw_core_get_registry(core, PW_VERSION_REGISTRY,
									0 /* user_data size */);

	pw_registry_add_listener(registry, &registry_listener,
							 &registry_events, (void*)&nodes);

	static const struct pw_core_events core_events = {
		.version = PW_VERSION_CORE_EVENTS,
		.done = on_core_done,
	};

	struct roundtrip_data d = { .loop = loop };
	struct spa_hook core_listener;
	int err;

	pw_core_add_listener(core, &core_listener, &core_events, &d);

	d.pending = pw_core_sync(core, PW_ID_CORE, 0);

	if ((err = pw_main_loop_run(loop)) < 0)
		qDebug() << "main_loop_run error: " << err << "!\n";

	spa_hook_remove(&core_listener);

	pw_proxy_destroy((struct pw_proxy*)registry);
	pw_core_disconnect(core);
	pw_context_destroy(context);
	pw_main_loop_destroy(loop);
}

int PipeWireModel::rowCount(const QModelIndex &parent) const
{
	// For list models only the root node (an invalid parent) should return the list's size. For all
	// other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
	if (parent.isValid())
		return 0;

	// FIXME: Implement me!
	return nodes.size();
}

QVariant PipeWireModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	// FIXME: Implement me!
	return nodes.at(index.row());
}
