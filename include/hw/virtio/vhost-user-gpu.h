/*
 * Vhost-user Gpu virtio device
 *
 * Copyright 2024 Red Hat, Inc.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef QEMU_VHOST_USER_GPU_H
#define QEMU_VHOST_USER_GPU_H

#include "hw/virtio/virtio.h"
#include "hw/virtio/vhost.h"
#include "hw/virtio/vhost-user.h"
#include "hw/virtio/vhost-user-base.h"

#define TYPE_VHOST_USER_GPU "vhost-user-gpu"
OBJECT_DECLARE_SIMPLE_TYPE(VHostUserGpu, VHOST_USER_GPU)

struct VHostUserGpu {
    /*< private >*/
    VHostUserBase parent;
    /*< public >*/
};

#endif /* QEMU_VHOST_USER_GPU_H */
