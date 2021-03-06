/*
 *  Ginkgo CADx Project
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

#pragma once
#include <api/iwidgets.h>
#include <api/controllers/ieventscontroller.h>
#include <widgets/observers/iobservadorchromacomplejo.h>
#include <vector>

class vtkImageData;

namespace GNC
{
namespace GCS
{
namespace Widgets
{

//---------------------------------------------------------------------
class EXTAPI WChromaComplejoBuilder : public GNC::GCS::Widgets::IWidgetBuilder, public GNC::GCS::Widgets::Notificadores::INotificadorChromaComplejo
{
public:
        typedef std::list<GNC::GCS::Nodo> TListaNodos;
        WChromaComplejoBuilder(GNC::GCS::IWidgetsManager* pManager, const GNC::GCS::TriggerButton& buttonMask, long gid, int numeroPuntos, GNC::GCS::Widgets::Observadores::IObservadorChromaComplejo* pObservador = NULL);

        ~WChromaComplejoBuilder();

        void SetNumeroPuntos(int numeroPuntos);

        virtual void OnMouseEvents(GNC::GCS::Events::EventoRaton&);

        virtual void OnKeyEvents(GNC::GCS::Events::EventoTeclado&);

        void DibujarVarita(GNC::GCS::Contexto3D* c);

        virtual void Render(GNC::GCS::Contexto3D* c);

        virtual GNC::GCS::Widgets::TipoCursor GetCursor();


protected:
        int                         m_NumMaxSemillas;
        GNC::GCS::Vector m_VerticesSeleccion[2];
        TListaNodos   m_ListaNodos;
        GNC::GCS::Vector m_PosCursor;
        bool                      m_MouseDown;
        Estado                   m_Estado;
        int m_numeroPuntos;
};

//---------------------------------------------------------------------

class EXTAPI WChromaComplejo : public GNC::GCS::Widgets::IWidget
{


        //region "Constructor y destructor"

public:
        typedef std::list<GNC::GCS::Nodo> TListaNodos;
        WChromaComplejo(IWidgetsManager* pManager, long vid, TListaNodos listaNodos, int numeroPuntos, bool isAgregar, const char* nombre, long gid, bool oculto = false);

        ~WChromaComplejo();

        //endregion

        //region "Interfaz especifica"

        virtual void OnMouseEvents(GNC::GCS::Events::EventoRaton&);

        virtual void OnKeyEvents(GNC::GCS::Events::EventoTeclado&);

        virtual bool HitTest(float x, float y, const GNC::GCS::Vector& umbral);

        virtual bool HitTest(GNC::GCS::Vector* vertices, int numVertices);

        virtual void Render(GNC::GCS::Contexto3D* c);

        virtual bool SoportaAutoBorrado() const
        {
                return false;
        }

        virtual bool EsMarcador() const
        {
                return false;
        }

        virtual bool DelimitaArea() const
        {
                return false;
        }
        //endregion

        virtual TListaNodos GetListaNodos();

        void SetNumeroPuntos(int numeroPuntos);

        bool EsAgregar()
        {
                return m_isAgregar;
        }

        //region "Estado interno"
private:
        bool            m_MouseDown;
        //endregion

        //region "Propiedades geometricas"
private:
        TListaNodos m_ListaNodos;
        int m_numeroPuntos;
        bool m_isAgregar;

public:
        friend std::ostream& operator<<(std::ostream& out, const WChromaComplejo& w)
        {
                out << ", GID=" << w.m_GID << ", TID=" << w.m_TID << " UID=" << w.m_UID << " ]";
                return out;
        }

        friend std::ostream& operator<<(std::ostream& out, const WChromaComplejo* w)
        {
                if (w == NULL) {
                        out << "[ NULL ]";
                } else {
                        out << *w;
                }
                return out;
        }
};
}
}
}
