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

package columbus.java.asg.base;

import columbus.IO;
import columbus.java.asg.*;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.base.Base Base} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public abstract class BaseImpl implements Base {

	protected Factory factory;

	protected int parent;

	@SuppressWarnings("unused")
	private static final LoggerHandler logger = new LoggerHandler(BaseImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected int id;

	public BaseImpl(int id, Factory factory) {
		this.id = id;
		this.factory = factory;
	}

	@Override
	public abstract NodeKind getNodeKind();

	@Override
	public Factory getFactory() {
		return factory;
	}

	protected void setParentEdge(int childId) {
		((BaseImpl)factory.getRef(childId)).parent = id;
	}

	protected void setParentEdge(Base childNode) {
		((BaseImpl)childNode).parent = id;
	}

	protected void removeParentEdge(int childId) {
		((BaseImpl)factory.getRef(childId)).parent = 0;
	}

	protected void removeParentEdge(Base childNode) {
		((BaseImpl)childNode).parent = 0;
	}

	protected void setParent(int parentId) {
		parent = parentId;
	}

	@Override
	public Base getParent() {
		return parent == 0 ? null : factory.getRef(parent);
	}

	@Override
	public int getId() {
		return id;
	}

	protected void setId(int _id) {
		id = _id;
	}


	// ---------- Accept methods for Visitor ----------

	@Override
	public void accept(Visitor visitor) {
	}

	@Override
	public void acceptEnd(Visitor visitor) {
	}


	// ---------- Save ----------

	@Override
	public abstract void save(IO io);


	// ---------- Load ----------

	@Override
	public abstract void load(IO io);

}
