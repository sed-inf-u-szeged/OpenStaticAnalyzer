/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

package graphlib;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 * An abstract class which can store attributes.
 *
 */
public abstract class AttributeOwner {

	protected final List<Attribute> attributes = new LinkedList<Attribute>();

	/**
	 * The given attribute will be added to the attribute owner.
	 * 
	 * @param attribute The attribute we would like to add to the current attribute.
	 * @return The added attribute.
	 */
	public Attribute addAttribute(Attribute attribute) {
		attributes.add(attribute);
		return attribute;
	}

	/**
	 * The given attribute will be removed from the attribute owner.
	 * 
	 * @param attribute The attribute we would like to remove.
	 * @return True if the deletion was happened, false otherwise.
	 */
	public boolean deleteAttribute(Attribute attribute) {
		return attributes.remove(attribute);
	}

	/**
	 * The given attribute with the type and name will be removed from the attribute owner.
	 * 
	 * @param type Type of the attribute we would like to delete.
	 * @param name Name of the attribute we would like to delete.
	 * @return True if the deletion was happened, false otherwise.
	 */
	public boolean deleteAttribute(Attribute.aType type, String name) {
		boolean thereWasDelete = false;
		for (Attribute attribute : attributes) {
			if (attribute.getType().equals(type) && name.equals(attribute.getName())) {
				thereWasDelete = deleteAttribute(attribute);
			}
		}
		return thereWasDelete;
	}

	/**
	 * The given attribute with the type will be removed from the attribute owner.
	 * 
	 * @param type Type of the attributes we would like to delete.
	 * @return True if the deletion was happened, false otherwise.
	 */
	public boolean deleteAttribute(Attribute.aType type) {
		boolean thereWasDelete = false;
		for (Attribute attribute : attributes) {
			if (attribute.getType().equals(type)) {
				thereWasDelete = deleteAttribute(attribute);
			}
		}
		return thereWasDelete;
	}

	/**
	 * Returns with the attributes of the current attribute.
	 * 
	 * @return The attributes of the current attribute.
	 */
	public List<Attribute> getAttributes() {
		List<Attribute> ret = new ArrayList<Attribute>();
		for (Attribute attribute : attributes) {
			ret.add(attribute);
		}
		return ret;
	}

	/**
	 * It returns the attributes with the given type, name and context.
	 * 
	 * @param type Type of the attributes we would like to find.
	 * @param name Name of the attributes we would like to find.
	 * @param context Context of the attributes we would like to find.
	 * @return List of the attributes were found.
	 */
	public List<Attribute> findAttribute(Attribute.aType type, String name, String context) {
		List<Attribute> ret = new ArrayList<Attribute>();
		for (Attribute attribute : attributes) {
			if (attribute.getType().equals(type) && name.equals(attribute.getName())
					&& attribute.getContext().equals(context)) {
				ret.add(attribute);
			}
		}
		return ret;

	}

	/**
	 * It returns the attributes with the given type.
	 * 
	 * @param type Type of the attributes we would like to find.
	 * @return List of the attributes were found.
	 */
	public List<Attribute> findAttributeByType(Attribute.aType type) {
		List<Attribute> ret = new ArrayList<Attribute>();
		for (Attribute attribute : attributes) {
			if (attribute.getType().equals(type)) {
				ret.add(attribute);
			}
		}
		return ret;
	}

	/**
	 * It returns the attributes with the given name.
	 * 
	 * @param name Name of the attributes we would like to find.
	 * @return List of the attributes were found.
	 */
	public List<Attribute> findAttributeByName(String name) {
		List<Attribute> ret = new ArrayList<Attribute>();
		for (Attribute attribute : attributes) {
			if (attribute.getName().equals(name)) {
				ret.add(attribute);
			}
		}
		return ret;
	}

	/**
	 * It returns the attributes with the given context.
	 * 
	 * @param context Context of the attributes we would like to find.
	 * @return List of the attributes were found.
	 */
	public List<Attribute> findAttributeByContext(String context) {
		List<Attribute> ret = new ArrayList<Attribute>();
		for (Attribute attribute : attributes) {
			if (attribute.getContext().equals(context)) {
				ret.add(attribute);
			}
		}
		return ret;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((attributes == null) ? 0 : attributes.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		AttributeOwner other = (AttributeOwner) obj;
		if (attributes == null) {
			if (other.attributes != null)
				return false;
		} else if (!attributes.equals(other.attributes))
			return false;
		return true;
	}

}
