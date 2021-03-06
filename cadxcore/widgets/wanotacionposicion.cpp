/*
 * This file is part of Ginkgo CADx
 *
 * Copyright (c) 2015-2016 Gert Wollny
 * Copyright (c) 2008-2014 MetaEmotion S.L. All rights reserved.
 *
 * Ginkgo CADx is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with Ginkgo CADx; if not, see <http://www.gnu.org/licenses/>.
 *
 */


#include "wanotacionposicion.h"

#include <main/managers/widgetsmanager.h>
#include <eventos/mensajes.h>
#include <api/iannotator.h>
#include <main/entorno.h>
#include <main/controllers/controladoreventos.h>


//region "Constructor y destructor"

GNC::GCS::Widgets::WAnotacionPosicion::WAnotacionPosicion(IWidgetsManager* pManager, long vid, const char* nombre, long gid) : GNC::GCS::Widgets::IWidget(pManager, vid, nombre, gid)
{
        m_Oculto = false;
        m_TopLevel = true;
        m_ReservaRecursos = false;

        GTRACE("Anotador posicion creado");
}

GNC::GCS::Widgets::WAnotacionPosicion::~WAnotacionPosicion()
{
        GTRACE("Anotador posicion destruido");

        std::ostringstream os;
        os <<  GNC::Entorno::Instance()->GetApplicationName() << " " << GNC::Entorno::Instance()->GetGinkgoCopyRight();
        std::string mensaje = os.str();
        GNC::GCS::ControladorEventos::Instance()->ProcesarEvento(new GNC::GCS::Events::EventoMensajes(NULL,mensaje));
}

//endregion

//region "Interfaz generica"

void GNC::GCS::Widgets::WAnotacionPosicion::OnMouseEvents(GNC::GCS::Events::EventoRaton& evento)
{
        if(m_Oculto) {
                return;
        }

        if( evento.Moving() || evento.Dragging()) {
                if (m_pManager->GetAnnotator().IsValid()) {
                        std::string posstr = m_pManager->GetAnnotator()->GetPositionAnnotation(evento.c, evento.wP);
                        GNC::GCS::ControladorEventos::Instance()->ProcesarEvento(new GNC::GCS::Events::EventoMensajes(NULL,posstr));
                }
        }
}

void GNC::GCS::Widgets::WAnotacionPosicion::OnKeyEvents(GNC::GCS::Events::EventoTeclado& /*evento*/)
{
}

bool GNC::GCS::Widgets::WAnotacionPosicion::HitTest(float , float , const GNC::GCS::Vector&)
{
        return false;
}

bool GNC::GCS::Widgets::WAnotacionPosicion::HitTest(GNC::GCS::Vector* , int )
{
        return false;
}

void GNC::GCS::Widgets::WAnotacionPosicion::Render(GNC::GCS::Contexto3D* /*c*/)
{
}


void GNC::GCS::Widgets::WAnotacionPosicion::Seleccionar(bool )
{
}

void GNC::GCS::Widgets::WAnotacionPosicion::Iluminar(bool )
{
}

void GNC::GCS::Widgets::WAnotacionPosicion::Ocultar(bool oculto)
{
        if(oculto != m_Oculto) {
                m_Oculto = oculto;
        }
}



