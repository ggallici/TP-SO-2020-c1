/*
 * administrador_colas.c
 *
 *  Created on: 17 jun. 2020
 *      Author: utnso
 */

#include "administrador_colas.h"

t_administrador_colas* administrador_colas_crear() {
    t_administrador_colas* administrador_colas = malloc(sizeof(t_administrador_colas));
    administrador_colas->id_mensaje = 1;
    administrador_colas->colas = dictionary_create();

    for(t_tipo_mensaje tipo_mensaje = 0; tipo_mensaje < 6; tipo_mensaje++) {
        char* key = string_itoa(tipo_mensaje);
        dictionary_put(administrador_colas->colas, key, cola_crear());
        free(key);
    }

    pthread_mutex_init(&administrador_colas->mutex_id_mensaje, NULL);

    return administrador_colas;
}

t_cola* administrador_colas_get_cola_from(t_administrador_colas* administrador_colas, t_tipo_mensaje tipo_mensaje) {
    char* key = string_itoa(tipo_mensaje);
    t_cola* cola = dictionary_get(administrador_colas->colas, key);
    free(key);

    return cola;
}

void administrador_colas_asignar_id_mensaje_a(t_administrador_colas* administrador_colas, t_paquete* paquete) {
    pthread_mutex_lock(&administrador_colas->mutex_id_mensaje);
    paquete->header->id_mensaje = administrador_colas->id_mensaje++;
    pthread_mutex_unlock(&administrador_colas->mutex_id_mensaje);
}

t_mensaje_despachable* administrador_colas_find_mensaje_despachable_by_id(t_administrador_colas* administrador_colas, uint32_t id_mensaje) {
    t_mensaje_despachable* mensaje_despachable = NULL;

    for(t_tipo_mensaje tipo_mensaje = 0; mensaje_despachable == NULL && tipo_mensaje < dictionary_size(administrador_colas->colas); tipo_mensaje++) {
        t_cola* cola = administrador_colas_get_cola_from(administrador_colas, tipo_mensaje);

        mensaje_despachable = cola_find_mensaje_despachable_by_id(cola, id_mensaje);
    }

    return mensaje_despachable;
}