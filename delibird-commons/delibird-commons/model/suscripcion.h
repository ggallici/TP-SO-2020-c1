/*
 * suscripcion.h
 *
 *  Created on: 8 may. 2020
 *      Author: utnso
 */

#ifndef MODEL_SUSCRIPCION_H_
#define MODEL_SUSCRIPCION_H_

#include "mensaje.h"

typedef struct {
    t_tipo_mensaje tipo_mensaje;
    uint32_t tiempo;
} t_suscripcion;

t_suscripcion* suscripcion_crear(t_tipo_mensaje tipo_mensaje, uint32_t tiempo);

void suscripcion_liberar(t_suscripcion* suscripcion);

#endif /* MODEL_SUSCRIPCION_H_ */