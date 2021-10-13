/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

/*
 * VisitorOverride.cpp
 *
 *  Created on: Aug 4, 2010
 *      Author: kissmarci
 */

#include "lim/inc/lim.h"

namespace columbus {
namespace lim {
namespace asg {

VisitorOverride::VisitorOverride(const Factory &f, OverrideRelations &override) :
  _factory(f), _overrides(override) {
}

void VisitorOverride::visit(const logical::Method &method, bool callVirtualBase) {
  base::Base *lim_parent = method.getParent();

  VisitorAbstractNodes::visit(method, callVirtualBase);

  if (Common::getIsClass(*lim_parent))
  {
    const logical::Class &c = static_cast<const logical::Class&> (*lim_parent);

    for(ListIterator<base::Component> parents_it = c.getBelongsToListIteratorBegin(); parents_it != c.getBelongsToListIteratorEnd(); ++parents_it)
    {
      const base::Base &b = *parents_it;

      if (Common::getIsClass(b))
      {
        const logical::Class &parent = static_cast<const logical::Class&>(b);
        for(ListIterator<base::Component> members_it = parent.getBelongsToListIteratorBegin(); members_it != parent.getBelongsToListIteratorEnd(); ++members_it)
        {
          const logical::Member &member = static_cast<const logical::Member&> (_factory.getRef(members_it->getId()));
          if (Common::getIsMethod(member))
          {
            const logical::Method &method_node = static_cast<const logical::Method&> (member);
            if (_getIsOverride(method, method_node))
            {
              _overrides._addOverride(method, method_node);
            }
          }
          else
          {
            continue;
          }
        }
      }
    }
  }

  if (Common::getIsClassGenericInstance(*lim_parent))
  {
    //TODO ell
    //TODO extrem esetek figyelese, a genericInstance-ok altal fellepo tipusegyezes vizsgalata
    const base::Base &b = ((type::TypeFormerType&) *lim_parent);//.getInstantiates());
    const logical::Class &c = static_cast<const logical::ClassGeneric&> (b);
    //ListIterator member_it = c.getMemberListIterator();
    //while (member_it.hasNext())
    for(ListIterator<base::Component> member_it = c.getBelongsToListIteratorBegin(); member_it != c.getBelongsToListIteratorEnd(); ++member_it)
    {
      const logical::Member &member = static_cast<const logical::Member&> (_factory.getRef(member_it->getId()));
      if (Common::getIsMethod(member))
      {
        const logical::Method &method_node = static_cast<const logical::Method&> (member);
        if (_getIsOverride(method, method_node))
        {
          _overrides._addOverride(method, method_node);
        }
      }
      else
      {
        continue;
      }
    }
  }
}

//TODO Egyelore a lim-ben felfedezett const property hianya miatt
//ez az algoritmus nem működik megfelelően. Az override-hoz ennek is meg kell egyezni.

bool VisitorOverride::_getIsOverride(const logical::Method &m1, const logical::Method &m2) const {

  if (m1.getName().compare(m2.getName()) != 0)
  {
    return false;
  }

  if (m1.getParameterSize() != m2.getParameterSize())
  {
    return false;
  }

  if (m1.getIsStatic() != m2.getIsStatic())
  {
    return false;
  }

  ListIterator<logical::Parameter> m1_params = m1.getParameterListIteratorBegin();
  ListIterator<logical::Parameter> m2_params = m2.getParameterListIteratorBegin();

  while (m1_params != m1.getParameterListIteratorEnd())
  {
    const logical::Parameter &p1 = static_cast<const logical::Parameter&> (*(++m1_params));
    const logical::Parameter &p2 = static_cast<const logical::Parameter&> (*(++m2_params));

    //Itt azonos grafban vagyunk, ezert azonos tipus eseten azonos node-ra kell mutatnia
    //a tipus reprezentacionak.
    if (p1.getType() != p2.getType())
    {
      return false;
    }
  }

  if (Common::getIsMethodGeneric(m1) && Common::getIsMethodGeneric(m2))
  {
    const logical::MethodGeneric &mg1 = static_cast<const logical::MethodGeneric&> (m1);
    const logical::MethodGeneric &mg2 = static_cast<const logical::MethodGeneric&> (m2);

    if (mg1.getGenericParameterSize() != mg2.getGenericParameterSize())
    {
      return false;
    }

    ListIterator<logical::GenericParameter> genIterator1 = mg1.getGenericParameterListIteratorBegin();
    ListIterator<logical::GenericParameter> genIterator2 = mg2.getGenericParameterListIteratorBegin();

    while (genIterator1 != mg1.getGenericParameterListIteratorEnd())
    {
      const logical::GenericParameter &gp1 = static_cast<const logical::GenericParameter&> (*(++genIterator1));
      const logical::GenericParameter &gp2 = static_cast<const logical::GenericParameter&> (*(++genIterator2));

      if (gp1.getGenericParameterKind() != gp2.getGenericParameterKind())
      {
        return false;
      }

      ListIterator<type::Type> constr1 = gp1.getParameterConstraintListIteratorBegin();
      ListIterator<type::Type> constr2 = gp2.getParameterConstraintListIteratorBegin();

      while (constr1 != gp1.getParameterConstraintListIteratorEnd())
      {
        ++constr1;
        ++constr2;
        if (constr1->getId() != constr2->getId())
        {
          return false;
        }
      }
    }
  }

  return true;
}

}
}
}

