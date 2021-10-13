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

package columbus.java.asg.type;

import columbus.IO;
import columbus.java.asg.*;
import columbus.java.asg.base.BaseImpl;
import columbus.java.asg.base.Base;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.Visitor;
import columbus.logger.LoggerHandler;

/**
 * Implementation class for the {@link columbus.java.asg.type.UnionType UnionType} node.
 * <p><b>WARNING: For internal use only.</b></p>
 */
public class UnionTypeImpl extends BaseImpl implements UnionType {

	@SuppressWarnings("unused")
	private static final LoggerHandler logger = new LoggerHandler(UnionTypeImpl.class, columbus.java.asg.Constant.LoggerPropertyFile);
	protected EdgeList<Type> _alternatives;

	public UnionTypeImpl(int id, Factory factory) {
		super(id, factory);
	}

	@Override
	public NodeKind getNodeKind() {
		return NodeKind.ndkUnionType;
	}

	@Override
	public EdgeIterator<Type> getAlternativesIterator() {
		if (_alternatives == null)
			return EdgeList.<Type>emptyList().iterator();
		else
			return _alternatives.iterator();
	}

	@Override
	public boolean getAlternativesIsEmpty() {
		if (_alternatives == null)
			return true;
		else
			return _alternatives.isEmpty();
	}

	@Override
	public int getAlternativesSize() {
		if (_alternatives == null)
			return 0;
		else
			return _alternatives.size();
	}

	@Override
	public void addAlternatives(int _id) {
		if (!factory.getExist(_id))
			throw new JavaException(logger.formatMessage("ex.java.Node.No_end_point"));

		Base _node = factory.getRef(_id);
		if (Common.getIsBaseClassKind(_node.getNodeKind(), NodeKind.ndkType)) {
			if (_alternatives == null)
				_alternatives = new EdgeList<Type>(factory);
			_alternatives.add(_id);
		} else {
			throw new JavaException(logger.formatMessage("ex.java.Node.Invalid","NodeKind", _node.getNodeKind() ));
		}
	}

	@Override
	public void addAlternatives(Type _node) {
		if (_alternatives == null)
			_alternatives = new EdgeList<Type>(factory);
		_alternatives.add(_node);
	}


	// ---------- Accept methods for Visitor ----------

	@Override
	public void accept(Visitor visitor) {
		visitor.visit(this, true);
	}

	@Override
	public void acceptEnd(Visitor visitor) {
		visitor.visitEnd(this, true);
	}


	// ---------- Save ----------

	@Override
	public void save(IO io) {
		io.writeInt4(id);
		io.writeUShort2(getNodeKind().ordinal());


		if (_alternatives != null) {
			EdgeIterator<Type> it = getAlternativesIterator();
			while (it.hasNext()) {
				io.writeInt4(it.next().getId());
			}
		}
		io.writeInt4(0);
	}


	// ---------- Load ----------

	@Override
	public void load(IO io) {
		int _id;



		_id = io.readInt4();
		if (_id != 0) {
			_alternatives = new EdgeList<Type>(factory);
			while (_id != 0) {
				_alternatives.add(_id);
				_id = io.readInt4();
			}
		}
	}

}
