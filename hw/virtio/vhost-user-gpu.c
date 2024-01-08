/*
 * Vhost-user GPU virtio device
 *
 * Copyright (c) 2024 Red Hat
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "hw/qdev-properties.h"
#include "hw/virtio/virtio-bus.h"
#include "hw/virtio/vhost-user-gpu.h"
#include "standard-headers/linux/virtio_ids.h"
#include "standard-headers/linux/virtio_gpu.h"

static Property vgpu_properties[] = {
    DEFINE_PROP_CHR("chardev", VHostUserBase, chardev),
    DEFINE_PROP_END_OF_LIST(),
};

static void vgpu_realize(DeviceState *dev, Error **errp)
{
    VHostUserBase *vub = VHOST_USER_BASE(dev);
    VHostUserBaseClass *vubc = VHOST_USER_BASE_GET_CLASS(dev);

    /* Fixed for GPU */
    vub->virtio_id = VIRTIO_ID_GPU;
    vub->num_vqs = 2;
    vub->config_size = sizeof(struct virtio_gpu_config);

    vubc->parent_realize(dev, errp);
}

static const VMStateDescription vu_gpu_vmstate = {
    .name = "vhost-user-gpu",
    .unmigratable = 1,
};

static void vu_gpu_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    VHostUserBaseClass *vubc = VHOST_USER_BASE_CLASS(klass);

    dc->vmsd = &vu_gpu_vmstate;
    device_class_set_props(dc, vgpu_properties);
    device_class_set_parent_realize(dc, vgpu_realize,
                                    &vubc->parent_realize);
    set_bit(DEVICE_CATEGORY_DISPLAY, dc->categories);
}

static const TypeInfo vu_gpu_info = {
    .name = TYPE_VHOST_USER_GPU,
    .parent = TYPE_VHOST_USER_BASE,
    .instance_size = sizeof(VHostUserGpu),
    .class_init = vu_gpu_class_init,
};

static void vu_gpu_register_types(void)
{
    type_register_static(&vu_gpu_info);
}

type_init(vu_gpu_register_types)
