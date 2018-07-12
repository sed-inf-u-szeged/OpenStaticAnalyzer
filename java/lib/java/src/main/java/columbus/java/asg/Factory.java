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

package columbus.java.asg;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import columbus.ByteArray;
import columbus.CsiHeader;
import columbus.IO;
import columbus.StrTable;
import columbus.IO.IOMode;
import columbus.StrTable.StrType;
import columbus.java.asg.algorithms.AlgorithmPreorder;
import columbus.java.asg.base.Base;
import columbus.java.asg.struc.Package;
import columbus.java.asg.enums.*;
import columbus.java.asg.visitors.VisitorSave;
import columbus.logger.LoggerHandler;
import columbus.java.asg.base.BlockCommentImpl;
import columbus.java.asg.base.JavadocCommentImpl;
import columbus.java.asg.base.LineCommentImpl;
import columbus.java.asg.expr.ArrayAccessImpl;
import columbus.java.asg.expr.ArrayTypeExpressionImpl;
import columbus.java.asg.expr.AssignmentImpl;
import columbus.java.asg.expr.BooleanLiteralImpl;
import columbus.java.asg.expr.CharacterLiteralImpl;
import columbus.java.asg.expr.ClassLiteralImpl;
import columbus.java.asg.expr.ConditionalImpl;
import columbus.java.asg.expr.DoubleLiteralImpl;
import columbus.java.asg.expr.ErroneousImpl;
import columbus.java.asg.expr.ErroneousTypeExpressionImpl;
import columbus.java.asg.expr.ExternalTypeExpressionImpl;
import columbus.java.asg.expr.FieldAccessImpl;
import columbus.java.asg.expr.FloatLiteralImpl;
import columbus.java.asg.expr.IdentifierImpl;
import columbus.java.asg.expr.InfixExpressionImpl;
import columbus.java.asg.expr.InstanceOfImpl;
import columbus.java.asg.expr.IntegerLiteralImpl;
import columbus.java.asg.expr.LongLiteralImpl;
import columbus.java.asg.expr.MarkerAnnotationImpl;
import columbus.java.asg.expr.MethodInvocationImpl;
import columbus.java.asg.expr.NewArrayImpl;
import columbus.java.asg.expr.NewClassImpl;
import columbus.java.asg.expr.NormalAnnotationImpl;
import columbus.java.asg.expr.NullLiteralImpl;
import columbus.java.asg.expr.ParenthesizedExpressionImpl;
import columbus.java.asg.expr.PostfixExpressionImpl;
import columbus.java.asg.expr.PrefixExpressionImpl;
import columbus.java.asg.expr.PrimitiveTypeExpressionImpl;
import columbus.java.asg.expr.QualifiedTypeExpressionImpl;
import columbus.java.asg.expr.SimpleTypeExpressionImpl;
import columbus.java.asg.expr.SingleElementAnnotationImpl;
import columbus.java.asg.expr.StringLiteralImpl;
import columbus.java.asg.expr.SuperImpl;
import columbus.java.asg.expr.ThisImpl;
import columbus.java.asg.expr.TypeApplyExpressionImpl;
import columbus.java.asg.expr.TypeCastImpl;
import columbus.java.asg.expr.TypeUnionExpressionImpl;
import columbus.java.asg.expr.WildcardExpressionImpl;
import columbus.java.asg.statm.AssertImpl;
import columbus.java.asg.statm.BasicForImpl;
import columbus.java.asg.statm.BlockImpl;
import columbus.java.asg.statm.BreakImpl;
import columbus.java.asg.statm.CaseImpl;
import columbus.java.asg.statm.ContinueImpl;
import columbus.java.asg.statm.DefaultImpl;
import columbus.java.asg.statm.DoImpl;
import columbus.java.asg.statm.EmptyImpl;
import columbus.java.asg.statm.EnhancedForImpl;
import columbus.java.asg.statm.ExpressionStatementImpl;
import columbus.java.asg.statm.HandlerImpl;
import columbus.java.asg.statm.IfImpl;
import columbus.java.asg.statm.LabeledStatementImpl;
import columbus.java.asg.statm.ReturnImpl;
import columbus.java.asg.statm.SwitchImpl;
import columbus.java.asg.statm.SynchronizedImpl;
import columbus.java.asg.statm.ThrowImpl;
import columbus.java.asg.statm.TryImpl;
import columbus.java.asg.statm.WhileImpl;
import columbus.java.asg.struc.AnnotationTypeImpl;
import columbus.java.asg.struc.AnnotationTypeElementImpl;
import columbus.java.asg.struc.AnonymousClassImpl;
import columbus.java.asg.struc.ClassImpl;
import columbus.java.asg.struc.ClassGenericImpl;
import columbus.java.asg.struc.CompilationUnitImpl;
import columbus.java.asg.struc.EnumImpl;
import columbus.java.asg.struc.EnumConstantImpl;
import columbus.java.asg.struc.ImportImpl;
import columbus.java.asg.struc.InstanceInitializerBlockImpl;
import columbus.java.asg.struc.InterfaceImpl;
import columbus.java.asg.struc.InterfaceGenericImpl;
import columbus.java.asg.struc.MethodImpl;
import columbus.java.asg.struc.MethodGenericImpl;
import columbus.java.asg.struc.PackageImpl;
import columbus.java.asg.struc.PackageDeclarationImpl;
import columbus.java.asg.struc.ParameterImpl;
import columbus.java.asg.struc.StaticInitializerBlockImpl;
import columbus.java.asg.struc.TypeParameterImpl;
import columbus.java.asg.struc.VariableImpl;
import columbus.java.asg.type.ArrayTypeImpl;
import columbus.java.asg.type.BooleanTypeImpl;
import columbus.java.asg.type.ByteTypeImpl;
import columbus.java.asg.type.CharTypeImpl;
import columbus.java.asg.type.ClassTypeImpl;
import columbus.java.asg.type.DoubleTypeImpl;
import columbus.java.asg.type.ErrorTypeImpl;
import columbus.java.asg.type.FloatTypeImpl;
import columbus.java.asg.type.IntTypeImpl;
import columbus.java.asg.type.LongTypeImpl;
import columbus.java.asg.type.LowerBoundedWildcardTypeImpl;
import columbus.java.asg.type.MethodTypeImpl;
import columbus.java.asg.type.NoTypeImpl;
import columbus.java.asg.type.NullTypeImpl;
import columbus.java.asg.type.PackageTypeImpl;
import columbus.java.asg.type.ParameterizedTypeImpl;
import columbus.java.asg.type.ShortTypeImpl;
import columbus.java.asg.type.TypeVariableImpl;
import columbus.java.asg.type.UnboundedWildcardTypeImpl;
import columbus.java.asg.type.UnionTypeImpl;
import columbus.java.asg.type.UpperBoundedWildcardTypeImpl;
import columbus.java.asg.type.VoidTypeImpl;
import columbus.java.asg.base.BlockComment;
import columbus.java.asg.base.JavadocComment;
import columbus.java.asg.base.LineComment;
import columbus.java.asg.type.ArrayType;
import columbus.java.asg.type.BooleanType;
import columbus.java.asg.type.ByteType;
import columbus.java.asg.type.CharType;
import columbus.java.asg.type.ClassType;
import columbus.java.asg.type.DoubleType;
import columbus.java.asg.type.ErrorType;
import columbus.java.asg.type.FloatType;
import columbus.java.asg.type.IntType;
import columbus.java.asg.type.LongType;
import columbus.java.asg.type.LowerBoundedWildcardType;
import columbus.java.asg.type.MethodType;
import columbus.java.asg.type.NoType;
import columbus.java.asg.type.NullType;
import columbus.java.asg.type.PackageType;
import columbus.java.asg.type.ParameterizedType;
import columbus.java.asg.type.ShortType;
import columbus.java.asg.type.TypeVariable;
import columbus.java.asg.type.UnboundedWildcardType;
import columbus.java.asg.type.UnionType;
import columbus.java.asg.type.UpperBoundedWildcardType;
import columbus.java.asg.type.VoidType;

/**
 * Factory, which handles (creates, deletes, sets their properties) nodes.
 */
public final class Factory {

	private static final LoggerHandler logger = new LoggerHandler(Factory.class, Constant.LoggerPropertyFile);
	/** Reference to the StringTable. */
	private StrTable strTable;

	/** Container where the references to nodes are stored. */
	private ArrayList<Base> container = new ArrayList<Base>();

	/** Reference to the root. */
	private Package root;

	/** The Filter. */
	private Filter filter;

	/** Stores whether the filter is turned on or off. */
	private boolean filterOn;

	/** Map for storing special nodes and their inner representation. */
	private Map<ByteArray, Base> apspecNodes = new HashMap<ByteArray, Base>();
	/** Map for storing 'BooleanType' type special nodes and their inner representation. */
	private BooleanType apspecNodeBooleanType = null;
	/** Map for storing 'ByteType' type special nodes and their inner representation. */
	private ByteType apspecNodeByteType = null;
	/** Map for storing 'CharType' type special nodes and their inner representation. */
	private CharType apspecNodeCharType = null;
	/** Map for storing 'DoubleType' type special nodes and their inner representation. */
	private DoubleType apspecNodeDoubleType = null;
	/** Map for storing 'ErrorType' type special nodes and their inner representation. */
	private ErrorType apspecNodeErrorType = null;
	/** Map for storing 'FloatType' type special nodes and their inner representation. */
	private FloatType apspecNodeFloatType = null;
	/** Map for storing 'IntType' type special nodes and their inner representation. */
	private IntType apspecNodeIntType = null;
	/** Map for storing 'LongType' type special nodes and their inner representation. */
	private LongType apspecNodeLongType = null;
	/** Map for storing 'NoType' type special nodes and their inner representation. */
	private NoType apspecNodeNoType = null;
	/** Map for storing 'NullType' type special nodes and their inner representation. */
	private NullType apspecNodeNullType = null;
	/** Map for storing 'ShortType' type special nodes and their inner representation. */
	private ShortType apspecNodeShortType = null;
	/** Map for storing 'VoidType' type special nodes and their inner representation. */
	private VoidType apspecNodeVoidType = null;

	/**
	 * Nested iterator class which enumerates the nodes.
	 */
	public class Iterator {

	private final LoggerHandler logger = new LoggerHandler(Iterator.class, Constant.LoggerPropertyFile);

		private int i;
		private int size = container.size();

		/**
		 * Constructor.
		 */
		private Iterator() {
		}

		/**
		 * Examines the existence of the next node.
		 * @return Returns true if a next node exists.
		 */
		public boolean hasNext() {
			int j = i;
			while (j < size && (container.get(j) == null || getIsFiltered(j))) {
				++j;
			}
			return j < size;
		}

		/**
		 * Returns a reference of the next node ({@link columbus.java.asg.base.Base Base}).
		 * @return Reference of the next node.
		 */
		public Base next() {
			while (i < size && (container.get(i) == null || getIsFiltered(i))) {
				++i;
			}
			if (i >= size) {
				throw new JavaException(logger.formatMessage("ex.java.xxx.Next_element_does_not_exist"));
			}
			return container.get(i++);
		}
	}

	/**
	 * Constructor.
	 * @param st Reference to the StrTable.
	 */
	public Factory(StrTable st) {
		strTable = st;
		filter = new Filter(this);
		filterOn = true;
		root = (Package)createNode(NodeKind.ndkPackage, 100);
		root.setName("<root_package>");
		root.setQualifiedName("<root_package>");

		init();
	}

	protected void clear() {
		// Deleting all nodes from the factory
		container.clear();

		if (filter != null) {
			filter = new Filter(this);
		}

		apspecNodes.clear();
		apspecNodeBooleanType = null;
		apspecNodeByteType = null;
		apspecNodeCharType = null;
		apspecNodeDoubleType = null;
		apspecNodeErrorType = null;
		apspecNodeFloatType = null;
		apspecNodeIntType = null;
		apspecNodeLongType = null;
		apspecNodeNoType = null;
		apspecNodeNullType = null;
		apspecNodeShortType = null;
		apspecNodeVoidType = null;
	}

	/**
	 * Saves the graph.
	 * @param filename The graph is saved into this file.
	 * @param header   The header information (also will be saved).
	 */
	public void save(String filename, CsiHeader header) {
		save(filename, header, StrType.strDefault, true);
	}

	/**
	 * Saves the graph.
	 * @param filename The graph is saved into this file.
	 * @param header   The header information (also will be saved).
	 * @param strType  Type of StrTable entries to save.
	 * @param usedOnly Save only 'used' special nodes, or all of them.
	 */
	public void save(String filename, CsiHeader header, StrType strType, boolean usedOnly) {
		IO io = new IO(filename, IOMode.WRITE);

		// saving header ...
		header.add(CsiHeader.csih_Type, "JavaLanguage");
		header.add(CsiHeader.csih_APIVersion, Constant.APIVersion);
		header.add(CsiHeader.csih_BinaryVersion, Constant.BinaryVersion);

		header.write(io);

		// saving the ASG
		AlgorithmPreorder algPre = new AlgorithmPreorder();
		algPre.setVisitSpecialNodes(true, usedOnly);
		VisitorSave vSave = new VisitorSave(io);
		algPre.run(this, vSave);

		// Writing the ENDMARK!
		io.writeInt4(0); // NodeId
		io.writeUShort2(0); // NodeKind

		// saving string table ...
		strTable.save(io, strType);

		io.close();

	}

	/**
	 * Loads the graph.
	 * @param filename The graph is loaded from this file.
	 * @param header   The header information (also will be loaded).
	 */
	public void load(String filename, CsiHeader header) {
		clear();

		IO io = new IO(filename, IOMode.READ);

		// loading header ...
		header.read(io);

		// Checking the type
		String type = header.get(CsiHeader.csih_Type);
		if (type == null)
			throw new JavaException(logger.formatMessage("ex.java.Factory.Missing_file_type_information"));
		if (!type.equals("JavaLanguage"))
			throw new JavaException(logger.formatMessage("ex.java.Factory.Wrong_file_type_information"));

		// Checking API version
		String apiVersion = header.get(CsiHeader.csih_APIVersion);
		if (apiVersion == null)
			throw new JavaException(logger.formatMessage("ex.java.Factory.Missing_API_version_information"));
		if (!apiVersion.equals(Constant.APIVersion))
			throw new JavaException(logger.formatMessage("ex.java.Factory.Wrong_API_version", Constant.APIVersion , apiVersion ));

		// Checking binary version
		String binVersion = header.get(CsiHeader.csih_BinaryVersion);
		if (binVersion == null)
			throw new JavaException(logger.formatMessage("ex.java.Factory.Missing_binary_version_information"));
		if (!binVersion.equals(Constant.BinaryVersion))
			throw new JavaException(logger.formatMessage("ex.java.Factory.Wrong_binary_version", Constant.BinaryVersion , binVersion));

		// loading the ASG
		int id = io.readInt4();
		NodeKind kind = NodeKind.values()[io.readUShort2()];

		while (id != 0) {
			createNode(kind, id);
			container.get(id).load(io);

			id = io.readInt4();
			kind = NodeKind.values()[io.readUShort2()];
		}
		// loading the string table
		strTable.load(io);

		root = (Package)container.get(100);

		io.close();

		init();

	}

	/**
	 * Turns the Filter on.
	 */
	public void turnFilterOn() {
		filterOn = true;
	}

	/**
	 * Turns the Filter off.
	 */
	public void turnFilterOff() {
		filterOn = false;
	}

	/**
	 * Gives back the state of the Filter.
	 * @return Returns true if the Filter is turned on, otherwise returns false.
	 */
	public boolean getIsFilterTurnedOn() {
		return filterOn;
	}

	/**
	 * Initializes the filter.
	 */
	public void initializeFilter() {
		filter.initializeFilter();
	}

	/**
	 * Tells whether the given node is filtered or not.
	 * @param id            The id of the node.
	 * @throws JavaException Throws JavaException if the id is too large.
	 * @return Returns true if the Node is filtered and returns false if it isn't (or the filter mode is turned off).
	 */
	public boolean getIsFiltered(int id) {
		return !filterOn ? false : filter.getIsFiltered(id);
	}

	/**
	 * Filters out the given node and all of its descendants.
	 * @param id            The id of the node.
	 * @throws JavaException Throws JavaException id the id is too large (larger than the size of the Filter).
	 */
	public void setFiltered(int id) {
		filter.setFiltered(id);
	}

	/**
	 * Sets the state of the node, all of its descendants and all of its ancestors to not filtered.
	 * @param id            The id of the node.
	 * @throws JavaException Throws JavaException id the id is too large (larger than the size of the Filter).
	 */
	public void setNotFiltered(int id) {
		filter.setNotFiltered(id);
	}

	/**
	 * Filter out only the given node (without its children).
	 * @param id            The id of the node.
	 * @throws JavaException Throws JavaException id the id is too large (larger than the size of the Filter).
	 */
	public void setFilteredThisNodeOnly(int id) {
		filter.setFilteredThisNodeOnly(id);
	}

	/**
	 * Sets the state of the given node (without its children) to not filtered.
	 * @param id            The id of the node.
	 * @throws JavaException Throws JavaException id the id is too large (larger than the size of the Filter).
	 */
	public void setNotFilteredThisNodeOnly(int id) {
		filter.setNotFilteredThisNodeOnly(id);
	}

	/**
	 * Saves the filter.
	 * @param filename The name of the filter file.
	 */
	public void saveFilter(String filename) {
		filter.save(filename);
	}

	/**
	 * Loads the filter.
	 * @param filename The name of the filter file.
	 */
	public void loadFilter(String filename) {
		filter.load(filename);
	}

	/**
	 * Gives back a reference to the StringTable.
	 * @return Reference to the StringTable.
	 */
	public StrTable getStringTable() {
		return strTable;
	}

	/**
	 * Gives back a reference to the root node.
	 * @return The reference to the root node.
	 */
	public Package getRoot() {
		return root;
	}

	/**
	 * Decides whether it is a valid id or not.
	 * @param id The id whose validity is examined.
	 * @return Returns true if a node belongs to the id.
	 */
	public boolean getExist(int id) {
		if (container.size() <= id)
			//throw new JavaException(logger.formatMessage("ex.java.Factory.Invalid_id", id) );
			return false;
		return container.get(id) != null;
	}

	/**
	 * Gives back a reference to the node.
	 * @param id            The id of the node.
	 * @throws JavaException Throws JavaException if there is no node for the id.
	 * @return Reference to the node.
	 */
	public Base getRef(int id) {
		Base p = null;
		if (id < container.size())
			p = container.get(id);
		if (p == null)
			throw new JavaException(logger.formatMessage("ex.java.Factory.Invalid_id", id) );
		return p;
	}

	/**
	 * Gives back the NodeKind of a node.
	 * @param id            The id of the node.
	 * @throws JavaException Throws JavaException if there is no node for the id.
	 * @return The NodeKind of the node.
	 */
	public NodeKind getNodeKind(int id) {
		return getRef(id).getNodeKind();
	}

	/**
	 * Creates and returns an iterator, which enumerates the nodes in the graph.
	 * @return An iterator to the nodes.
	 */
	public Iterator iterator() {
		return new Iterator();
	}

	/**
	 * Returns the number of nodes.
	 * @return The number of nodes.
	 */
	public int size() {
		return container.size();
	}

	/**
	 * Tells whether the factory has nodes or not (O(n)).
	 * @return Returns true if there is not any node.
	 */
	public boolean isEmpty() {
		for (int i = 0; i < container.size(); i++)
			if (container.get(i) != null)
				return false;
		return true;
	}

	/**
	 * Creates a new node, insert it into the container and return with it.
	 * @param ndk           The kind of the node.
	 * @throws JavaException If an invalid (or an abstract) NodeKind is given, JavaException is thrown.
	 * @return Reference to the new node.
	 */
	public Base createNode(NodeKind ndk) {
		Base p = null;
		switch (ndk) {
			case ndkArrayAccess: p = new ArrayAccessImpl(container.size(), this); break;
			case ndkArrayTypeExpression: p = new ArrayTypeExpressionImpl(container.size(), this); break;
			case ndkAssignment: p = new AssignmentImpl(container.size(), this); break;
			case ndkBooleanLiteral: p = new BooleanLiteralImpl(container.size(), this); break;
			case ndkCharacterLiteral: p = new CharacterLiteralImpl(container.size(), this); break;
			case ndkClassLiteral: p = new ClassLiteralImpl(container.size(), this); break;
			case ndkConditional: p = new ConditionalImpl(container.size(), this); break;
			case ndkDoubleLiteral: p = new DoubleLiteralImpl(container.size(), this); break;
			case ndkErroneous: p = new ErroneousImpl(container.size(), this); break;
			case ndkErroneousTypeExpression: p = new ErroneousTypeExpressionImpl(container.size(), this); break;
			case ndkExternalTypeExpression: p = new ExternalTypeExpressionImpl(container.size(), this); break;
			case ndkFieldAccess: p = new FieldAccessImpl(container.size(), this); break;
			case ndkFloatLiteral: p = new FloatLiteralImpl(container.size(), this); break;
			case ndkIdentifier: p = new IdentifierImpl(container.size(), this); break;
			case ndkInfixExpression: p = new InfixExpressionImpl(container.size(), this); break;
			case ndkInstanceOf: p = new InstanceOfImpl(container.size(), this); break;
			case ndkIntegerLiteral: p = new IntegerLiteralImpl(container.size(), this); break;
			case ndkLongLiteral: p = new LongLiteralImpl(container.size(), this); break;
			case ndkMarkerAnnotation: p = new MarkerAnnotationImpl(container.size(), this); break;
			case ndkMethodInvocation: p = new MethodInvocationImpl(container.size(), this); break;
			case ndkNewArray: p = new NewArrayImpl(container.size(), this); break;
			case ndkNewClass: p = new NewClassImpl(container.size(), this); break;
			case ndkNormalAnnotation: p = new NormalAnnotationImpl(container.size(), this); break;
			case ndkNullLiteral: p = new NullLiteralImpl(container.size(), this); break;
			case ndkParenthesizedExpression: p = new ParenthesizedExpressionImpl(container.size(), this); break;
			case ndkPostfixExpression: p = new PostfixExpressionImpl(container.size(), this); break;
			case ndkPrefixExpression: p = new PrefixExpressionImpl(container.size(), this); break;
			case ndkPrimitiveTypeExpression: p = new PrimitiveTypeExpressionImpl(container.size(), this); break;
			case ndkQualifiedTypeExpression: p = new QualifiedTypeExpressionImpl(container.size(), this); break;
			case ndkSimpleTypeExpression: p = new SimpleTypeExpressionImpl(container.size(), this); break;
			case ndkSingleElementAnnotation: p = new SingleElementAnnotationImpl(container.size(), this); break;
			case ndkStringLiteral: p = new StringLiteralImpl(container.size(), this); break;
			case ndkSuper: p = new SuperImpl(container.size(), this); break;
			case ndkThis: p = new ThisImpl(container.size(), this); break;
			case ndkTypeApplyExpression: p = new TypeApplyExpressionImpl(container.size(), this); break;
			case ndkTypeCast: p = new TypeCastImpl(container.size(), this); break;
			case ndkTypeUnionExpression: p = new TypeUnionExpressionImpl(container.size(), this); break;
			case ndkWildcardExpression: p = new WildcardExpressionImpl(container.size(), this); break;
			case ndkAssert: p = new AssertImpl(container.size(), this); break;
			case ndkBasicFor: p = new BasicForImpl(container.size(), this); break;
			case ndkBlock: p = new BlockImpl(container.size(), this); break;
			case ndkBreak: p = new BreakImpl(container.size(), this); break;
			case ndkCase: p = new CaseImpl(container.size(), this); break;
			case ndkContinue: p = new ContinueImpl(container.size(), this); break;
			case ndkDefault: p = new DefaultImpl(container.size(), this); break;
			case ndkDo: p = new DoImpl(container.size(), this); break;
			case ndkEmpty: p = new EmptyImpl(container.size(), this); break;
			case ndkEnhancedFor: p = new EnhancedForImpl(container.size(), this); break;
			case ndkExpressionStatement: p = new ExpressionStatementImpl(container.size(), this); break;
			case ndkHandler: p = new HandlerImpl(container.size(), this); break;
			case ndkIf: p = new IfImpl(container.size(), this); break;
			case ndkLabeledStatement: p = new LabeledStatementImpl(container.size(), this); break;
			case ndkReturn: p = new ReturnImpl(container.size(), this); break;
			case ndkSwitch: p = new SwitchImpl(container.size(), this); break;
			case ndkSynchronized: p = new SynchronizedImpl(container.size(), this); break;
			case ndkThrow: p = new ThrowImpl(container.size(), this); break;
			case ndkTry: p = new TryImpl(container.size(), this); break;
			case ndkWhile: p = new WhileImpl(container.size(), this); break;
			case ndkAnnotationType: p = new AnnotationTypeImpl(container.size(), this); break;
			case ndkAnnotationTypeElement: p = new AnnotationTypeElementImpl(container.size(), this); break;
			case ndkAnonymousClass: p = new AnonymousClassImpl(container.size(), this); break;
			case ndkClass: p = new ClassImpl(container.size(), this); break;
			case ndkClassGeneric: p = new ClassGenericImpl(container.size(), this); break;
			case ndkCompilationUnit: p = new CompilationUnitImpl(container.size(), this); break;
			case ndkEnum: p = new EnumImpl(container.size(), this); break;
			case ndkEnumConstant: p = new EnumConstantImpl(container.size(), this); break;
			case ndkImport: p = new ImportImpl(container.size(), this); break;
			case ndkInstanceInitializerBlock: p = new InstanceInitializerBlockImpl(container.size(), this); break;
			case ndkInterface: p = new InterfaceImpl(container.size(), this); break;
			case ndkInterfaceGeneric: p = new InterfaceGenericImpl(container.size(), this); break;
			case ndkMethod: p = new MethodImpl(container.size(), this); break;
			case ndkMethodGeneric: p = new MethodGenericImpl(container.size(), this); break;
			case ndkPackage: p = new PackageImpl(container.size(), this); break;
			case ndkPackageDeclaration: p = new PackageDeclarationImpl(container.size(), this); break;
			case ndkParameter: p = new ParameterImpl(container.size(), this); break;
			case ndkStaticInitializerBlock: p = new StaticInitializerBlockImpl(container.size(), this); break;
			case ndkTypeParameter: p = new TypeParameterImpl(container.size(), this); break;
			case ndkVariable: p = new VariableImpl(container.size(), this); break;
			default: throw new JavaException(logger.formatMessage("ex.java.Factory.Invalid_kind", ndk  ) );
		}

		container.add(p);

		if (filter.size() < container.size())
			filter.resize();

		return p;
	}

	/**
	 * Creates a new node, insert it into the container and return with it.
	 * @param ndk           The kind of the node.
	 * @param id            The id of the new node.
	 * @throws JavaException If an invalid (or an abstract) NodeKind is given, JavaException is thrown.
	 * @return Reference to the new node.
	 */
	private Base createNode(NodeKind ndk, int id) {
		Base p = null;
		switch (ndk) {
			case ndkBlockComment: p = new BlockCommentImpl(id, this); break;
			case ndkJavadocComment: p = new JavadocCommentImpl(id, this); break;
			case ndkLineComment: p = new LineCommentImpl(id, this); break;
			case ndkArrayAccess: p = new ArrayAccessImpl(id, this); break;
			case ndkArrayTypeExpression: p = new ArrayTypeExpressionImpl(id, this); break;
			case ndkAssignment: p = new AssignmentImpl(id, this); break;
			case ndkBooleanLiteral: p = new BooleanLiteralImpl(id, this); break;
			case ndkCharacterLiteral: p = new CharacterLiteralImpl(id, this); break;
			case ndkClassLiteral: p = new ClassLiteralImpl(id, this); break;
			case ndkConditional: p = new ConditionalImpl(id, this); break;
			case ndkDoubleLiteral: p = new DoubleLiteralImpl(id, this); break;
			case ndkErroneous: p = new ErroneousImpl(id, this); break;
			case ndkErroneousTypeExpression: p = new ErroneousTypeExpressionImpl(id, this); break;
			case ndkExternalTypeExpression: p = new ExternalTypeExpressionImpl(id, this); break;
			case ndkFieldAccess: p = new FieldAccessImpl(id, this); break;
			case ndkFloatLiteral: p = new FloatLiteralImpl(id, this); break;
			case ndkIdentifier: p = new IdentifierImpl(id, this); break;
			case ndkInfixExpression: p = new InfixExpressionImpl(id, this); break;
			case ndkInstanceOf: p = new InstanceOfImpl(id, this); break;
			case ndkIntegerLiteral: p = new IntegerLiteralImpl(id, this); break;
			case ndkLongLiteral: p = new LongLiteralImpl(id, this); break;
			case ndkMarkerAnnotation: p = new MarkerAnnotationImpl(id, this); break;
			case ndkMethodInvocation: p = new MethodInvocationImpl(id, this); break;
			case ndkNewArray: p = new NewArrayImpl(id, this); break;
			case ndkNewClass: p = new NewClassImpl(id, this); break;
			case ndkNormalAnnotation: p = new NormalAnnotationImpl(id, this); break;
			case ndkNullLiteral: p = new NullLiteralImpl(id, this); break;
			case ndkParenthesizedExpression: p = new ParenthesizedExpressionImpl(id, this); break;
			case ndkPostfixExpression: p = new PostfixExpressionImpl(id, this); break;
			case ndkPrefixExpression: p = new PrefixExpressionImpl(id, this); break;
			case ndkPrimitiveTypeExpression: p = new PrimitiveTypeExpressionImpl(id, this); break;
			case ndkQualifiedTypeExpression: p = new QualifiedTypeExpressionImpl(id, this); break;
			case ndkSimpleTypeExpression: p = new SimpleTypeExpressionImpl(id, this); break;
			case ndkSingleElementAnnotation: p = new SingleElementAnnotationImpl(id, this); break;
			case ndkStringLiteral: p = new StringLiteralImpl(id, this); break;
			case ndkSuper: p = new SuperImpl(id, this); break;
			case ndkThis: p = new ThisImpl(id, this); break;
			case ndkTypeApplyExpression: p = new TypeApplyExpressionImpl(id, this); break;
			case ndkTypeCast: p = new TypeCastImpl(id, this); break;
			case ndkTypeUnionExpression: p = new TypeUnionExpressionImpl(id, this); break;
			case ndkWildcardExpression: p = new WildcardExpressionImpl(id, this); break;
			case ndkAssert: p = new AssertImpl(id, this); break;
			case ndkBasicFor: p = new BasicForImpl(id, this); break;
			case ndkBlock: p = new BlockImpl(id, this); break;
			case ndkBreak: p = new BreakImpl(id, this); break;
			case ndkCase: p = new CaseImpl(id, this); break;
			case ndkContinue: p = new ContinueImpl(id, this); break;
			case ndkDefault: p = new DefaultImpl(id, this); break;
			case ndkDo: p = new DoImpl(id, this); break;
			case ndkEmpty: p = new EmptyImpl(id, this); break;
			case ndkEnhancedFor: p = new EnhancedForImpl(id, this); break;
			case ndkExpressionStatement: p = new ExpressionStatementImpl(id, this); break;
			case ndkHandler: p = new HandlerImpl(id, this); break;
			case ndkIf: p = new IfImpl(id, this); break;
			case ndkLabeledStatement: p = new LabeledStatementImpl(id, this); break;
			case ndkReturn: p = new ReturnImpl(id, this); break;
			case ndkSwitch: p = new SwitchImpl(id, this); break;
			case ndkSynchronized: p = new SynchronizedImpl(id, this); break;
			case ndkThrow: p = new ThrowImpl(id, this); break;
			case ndkTry: p = new TryImpl(id, this); break;
			case ndkWhile: p = new WhileImpl(id, this); break;
			case ndkAnnotationType: p = new AnnotationTypeImpl(id, this); break;
			case ndkAnnotationTypeElement: p = new AnnotationTypeElementImpl(id, this); break;
			case ndkAnonymousClass: p = new AnonymousClassImpl(id, this); break;
			case ndkClass: p = new ClassImpl(id, this); break;
			case ndkClassGeneric: p = new ClassGenericImpl(id, this); break;
			case ndkCompilationUnit: p = new CompilationUnitImpl(id, this); break;
			case ndkEnum: p = new EnumImpl(id, this); break;
			case ndkEnumConstant: p = new EnumConstantImpl(id, this); break;
			case ndkImport: p = new ImportImpl(id, this); break;
			case ndkInstanceInitializerBlock: p = new InstanceInitializerBlockImpl(id, this); break;
			case ndkInterface: p = new InterfaceImpl(id, this); break;
			case ndkInterfaceGeneric: p = new InterfaceGenericImpl(id, this); break;
			case ndkMethod: p = new MethodImpl(id, this); break;
			case ndkMethodGeneric: p = new MethodGenericImpl(id, this); break;
			case ndkPackage: p = new PackageImpl(id, this); break;
			case ndkPackageDeclaration: p = new PackageDeclarationImpl(id, this); break;
			case ndkParameter: p = new ParameterImpl(id, this); break;
			case ndkStaticInitializerBlock: p = new StaticInitializerBlockImpl(id, this); break;
			case ndkTypeParameter: p = new TypeParameterImpl(id, this); break;
			case ndkVariable: p = new VariableImpl(id, this); break;
			case ndkArrayType: p = new ArrayTypeImpl(id, this); break;
			case ndkBooleanType: p = new BooleanTypeImpl(id, this); break;
			case ndkByteType: p = new ByteTypeImpl(id, this); break;
			case ndkCharType: p = new CharTypeImpl(id, this); break;
			case ndkClassType: p = new ClassTypeImpl(id, this); break;
			case ndkDoubleType: p = new DoubleTypeImpl(id, this); break;
			case ndkErrorType: p = new ErrorTypeImpl(id, this); break;
			case ndkFloatType: p = new FloatTypeImpl(id, this); break;
			case ndkIntType: p = new IntTypeImpl(id, this); break;
			case ndkLongType: p = new LongTypeImpl(id, this); break;
			case ndkLowerBoundedWildcardType: p = new LowerBoundedWildcardTypeImpl(id, this); break;
			case ndkMethodType: p = new MethodTypeImpl(id, this); break;
			case ndkNoType: p = new NoTypeImpl(id, this); break;
			case ndkNullType: p = new NullTypeImpl(id, this); break;
			case ndkPackageType: p = new PackageTypeImpl(id, this); break;
			case ndkParameterizedType: p = new ParameterizedTypeImpl(id, this); break;
			case ndkShortType: p = new ShortTypeImpl(id, this); break;
			case ndkTypeVariable: p = new TypeVariableImpl(id, this); break;
			case ndkUnboundedWildcardType: p = new UnboundedWildcardTypeImpl(id, this); break;
			case ndkUnionType: p = new UnionTypeImpl(id, this); break;
			case ndkUpperBoundedWildcardType: p = new UpperBoundedWildcardTypeImpl(id, this); break;
			case ndkVoidType: p = new VoidTypeImpl(id, this); break;
			default: throw new JavaException(logger.formatMessage( "ex.java.Factory.Invalid_kind", ndk ) );
		}

		if (container.size() < id)
			container.addAll(Collections.<Base>nCopies(id - container.size(), null));

		if (container.size() == id)
			container.add(p);
		else
			container.set(id, p);

		if (filter.size() < container.size())
			filter.resize();

		return p;
	}

	/**
	 * Stores Range data in a ByteArray.
	 */
	private void storeRangeData(ByteArray ba, Range range) {
		ba.append(strTable.set(range.getPath()));
		ba.append(range.getLine());
		ba.append(range.getCol());
		ba.append(range.getEndLine());
		ba.append(range.getEndCol());
		ba.append(range.getWideLine());
		ba.append(range.getWideCol());
		ba.append(range.getWideEndLine());
		ba.append(range.getWideEndCol());
	}

	/**
	 * Creates a new {@link columbus.java.asg.base.BlockComment BlockComment} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public BlockComment createBlockComment(Range PositionedWithoutComment_position, String Comment_text) {
		ByteArray ba = new ByteArray();
		ba.append(NodeKind.ndkBlockComment.ordinal());
		storeRangeData(ba, PositionedWithoutComment_position);
		ba.append(strTable.set(Comment_text));

		Base b = apspecNodes.get(ba);
		if (b != null) {
			return (BlockComment)b;
		}

		BlockComment node = (BlockComment)createNode(NodeKind.ndkBlockComment, container.size());
		node.setPosition(PositionedWithoutComment_position);
		node.setText(Comment_text);
		apspecNodes.put(ba, node);
		return node;
	}

	/**
	 * Creates a new {@link columbus.java.asg.base.JavadocComment JavadocComment} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public JavadocComment createJavadocComment(Range PositionedWithoutComment_position, String Comment_text) {
		ByteArray ba = new ByteArray();
		ba.append(NodeKind.ndkJavadocComment.ordinal());
		storeRangeData(ba, PositionedWithoutComment_position);
		ba.append(strTable.set(Comment_text));

		Base b = apspecNodes.get(ba);
		if (b != null) {
			return (JavadocComment)b;
		}

		JavadocComment node = (JavadocComment)createNode(NodeKind.ndkJavadocComment, container.size());
		node.setPosition(PositionedWithoutComment_position);
		node.setText(Comment_text);
		apspecNodes.put(ba, node);
		return node;
	}

	/**
	 * Creates a new {@link columbus.java.asg.base.LineComment LineComment} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public LineComment createLineComment(Range PositionedWithoutComment_position, String Comment_text) {
		ByteArray ba = new ByteArray();
		ba.append(NodeKind.ndkLineComment.ordinal());
		storeRangeData(ba, PositionedWithoutComment_position);
		ba.append(strTable.set(Comment_text));

		Base b = apspecNodes.get(ba);
		if (b != null) {
			return (LineComment)b;
		}

		LineComment node = (LineComment)createNode(NodeKind.ndkLineComment, container.size());
		node.setPosition(PositionedWithoutComment_position);
		node.setText(Comment_text);
		apspecNodes.put(ba, node);
		return node;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.ArrayType ArrayType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public ArrayType createArrayType(int ArrayType_size, int ArrayType_componentType) {
		ByteArray ba = new ByteArray();
		ba.append(NodeKind.ndkArrayType.ordinal());
		ba.append(ArrayType_size);
		ba.append(ArrayType_componentType);

		Base b = apspecNodes.get(ba);
		if (b != null) {
			return (ArrayType)b;
		}

		ArrayType node = (ArrayType)createNode(NodeKind.ndkArrayType, container.size());
		node.setSize(ArrayType_size);
		if (ArrayType_componentType != 0)
			node.setComponentType(ArrayType_componentType);
		apspecNodes.put(ba, node);
		return node;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.BooleanType BooleanType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public BooleanType createBooleanType() {
		if (apspecNodeBooleanType == null) {
			apspecNodeBooleanType = (BooleanType)createNode(NodeKind.ndkBooleanType, container.size());
		}
		return apspecNodeBooleanType;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.ByteType ByteType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public ByteType createByteType() {
		if (apspecNodeByteType == null) {
			apspecNodeByteType = (ByteType)createNode(NodeKind.ndkByteType, container.size());
		}
		return apspecNodeByteType;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.CharType CharType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public CharType createCharType() {
		if (apspecNodeCharType == null) {
			apspecNodeCharType = (CharType)createNode(NodeKind.ndkCharType, container.size());
		}
		return apspecNodeCharType;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.ClassType ClassType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public ClassType createClassType(int ScopedType_owner, int ClassType_refersTo) {
		ByteArray ba = new ByteArray();
		ba.append(NodeKind.ndkClassType.ordinal());
		ba.append(ScopedType_owner);
		ba.append(ClassType_refersTo);

		Base b = apspecNodes.get(ba);
		if (b != null) {
			return (ClassType)b;
		}

		ClassType node = (ClassType)createNode(NodeKind.ndkClassType, container.size());
		if (ScopedType_owner != 0)
			node.setOwner(ScopedType_owner);
		if (ClassType_refersTo != 0)
			node.setRefersTo(ClassType_refersTo);
		apspecNodes.put(ba, node);
		return node;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.DoubleType DoubleType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public DoubleType createDoubleType() {
		if (apspecNodeDoubleType == null) {
			apspecNodeDoubleType = (DoubleType)createNode(NodeKind.ndkDoubleType, container.size());
		}
		return apspecNodeDoubleType;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.ErrorType ErrorType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public ErrorType createErrorType() {
		if (apspecNodeErrorType == null) {
			apspecNodeErrorType = (ErrorType)createNode(NodeKind.ndkErrorType, container.size());
		}
		return apspecNodeErrorType;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.FloatType FloatType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public FloatType createFloatType() {
		if (apspecNodeFloatType == null) {
			apspecNodeFloatType = (FloatType)createNode(NodeKind.ndkFloatType, container.size());
		}
		return apspecNodeFloatType;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.IntType IntType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public IntType createIntType() {
		if (apspecNodeIntType == null) {
			apspecNodeIntType = (IntType)createNode(NodeKind.ndkIntType, container.size());
		}
		return apspecNodeIntType;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.LongType LongType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public LongType createLongType() {
		if (apspecNodeLongType == null) {
			apspecNodeLongType = (LongType)createNode(NodeKind.ndkLongType, container.size());
		}
		return apspecNodeLongType;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.LowerBoundedWildcardType LowerBoundedWildcardType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public LowerBoundedWildcardType createLowerBoundedWildcardType(int WildcardType_bound) {
		ByteArray ba = new ByteArray();
		ba.append(NodeKind.ndkLowerBoundedWildcardType.ordinal());
		ba.append(WildcardType_bound);

		Base b = apspecNodes.get(ba);
		if (b != null) {
			return (LowerBoundedWildcardType)b;
		}

		LowerBoundedWildcardType node = (LowerBoundedWildcardType)createNode(NodeKind.ndkLowerBoundedWildcardType, container.size());
		if (WildcardType_bound != 0)
			node.setBound(WildcardType_bound);
		apspecNodes.put(ba, node);
		return node;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.MethodType MethodType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public MethodType createMethodType(int MethodType_returnType, List<Integer> MethodType_parameterTypes, List<Integer> MethodType_thrownTypes) {
		ByteArray ba = new ByteArray();
		ba.append(NodeKind.ndkMethodType.ordinal());
		ba.append(MethodType_returnType);
		for (int i : MethodType_parameterTypes) {
			ba.append(i);
		}
		ba.append((byte)0);
		for (int i : MethodType_thrownTypes) {
			ba.append(i);
		}
		ba.append((byte)0);

		Base b = apspecNodes.get(ba);
		if (b != null) {
			return (MethodType)b;
		}

		MethodType node = (MethodType)createNode(NodeKind.ndkMethodType, container.size());
		if (MethodType_returnType != 0)
			node.setReturnType(MethodType_returnType);
		for (int i : MethodType_parameterTypes) {
			node.addParameterTypes(i);
		}
		for (int i : MethodType_thrownTypes) {
			node.addThrownTypes(i);
		}
		apspecNodes.put(ba, node);
		return node;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.NoType NoType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public NoType createNoType() {
		if (apspecNodeNoType == null) {
			apspecNodeNoType = (NoType)createNode(NodeKind.ndkNoType, container.size());
		}
		return apspecNodeNoType;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.NullType NullType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public NullType createNullType() {
		if (apspecNodeNullType == null) {
			apspecNodeNullType = (NullType)createNode(NodeKind.ndkNullType, container.size());
		}
		return apspecNodeNullType;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.PackageType PackageType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public PackageType createPackageType(int PackageType_refersTo) {
		ByteArray ba = new ByteArray();
		ba.append(NodeKind.ndkPackageType.ordinal());
		ba.append(PackageType_refersTo);

		Base b = apspecNodes.get(ba);
		if (b != null) {
			return (PackageType)b;
		}

		PackageType node = (PackageType)createNode(NodeKind.ndkPackageType, container.size());
		if (PackageType_refersTo != 0)
			node.setRefersTo(PackageType_refersTo);
		apspecNodes.put(ba, node);
		return node;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.ParameterizedType ParameterizedType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public ParameterizedType createParameterizedType(int ScopedType_owner, int ParameterizedType_rawType, List<Integer> ParameterizedType_argumentTypes) {
		ByteArray ba = new ByteArray();
		ba.append(NodeKind.ndkParameterizedType.ordinal());
		ba.append(ScopedType_owner);
		ba.append(ParameterizedType_rawType);
		for (int i : ParameterizedType_argumentTypes) {
			ba.append(i);
		}
		ba.append((byte)0);

		Base b = apspecNodes.get(ba);
		if (b != null) {
			return (ParameterizedType)b;
		}

		ParameterizedType node = (ParameterizedType)createNode(NodeKind.ndkParameterizedType, container.size());
		if (ScopedType_owner != 0)
			node.setOwner(ScopedType_owner);
		if (ParameterizedType_rawType != 0)
			node.setRawType(ParameterizedType_rawType);
		for (int i : ParameterizedType_argumentTypes) {
			node.addArgumentTypes(i);
		}
		apspecNodes.put(ba, node);
		return node;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.ShortType ShortType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public ShortType createShortType() {
		if (apspecNodeShortType == null) {
			apspecNodeShortType = (ShortType)createNode(NodeKind.ndkShortType, container.size());
		}
		return apspecNodeShortType;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.TypeVariable TypeVariable} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public TypeVariable createTypeVariable(int TypeVariable_refersTo) {
		ByteArray ba = new ByteArray();
		ba.append(NodeKind.ndkTypeVariable.ordinal());
		ba.append(TypeVariable_refersTo);

		Base b = apspecNodes.get(ba);
		if (b != null) {
			return (TypeVariable)b;
		}

		TypeVariable node = (TypeVariable)createNode(NodeKind.ndkTypeVariable, container.size());
		if (TypeVariable_refersTo != 0)
			node.setRefersTo(TypeVariable_refersTo);
		apspecNodes.put(ba, node);
		return node;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.UnboundedWildcardType UnboundedWildcardType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public UnboundedWildcardType createUnboundedWildcardType(int WildcardType_bound) {
		ByteArray ba = new ByteArray();
		ba.append(NodeKind.ndkUnboundedWildcardType.ordinal());
		ba.append(WildcardType_bound);

		Base b = apspecNodes.get(ba);
		if (b != null) {
			return (UnboundedWildcardType)b;
		}

		UnboundedWildcardType node = (UnboundedWildcardType)createNode(NodeKind.ndkUnboundedWildcardType, container.size());
		if (WildcardType_bound != 0)
			node.setBound(WildcardType_bound);
		apspecNodes.put(ba, node);
		return node;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.UnionType UnionType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public UnionType createUnionType(List<Integer> UnionType_alternatives) {
		ByteArray ba = new ByteArray();
		ba.append(NodeKind.ndkUnionType.ordinal());
		for (int i : UnionType_alternatives) {
			ba.append(i);
		}
		ba.append((byte)0);

		Base b = apspecNodes.get(ba);
		if (b != null) {
			return (UnionType)b;
		}

		UnionType node = (UnionType)createNode(NodeKind.ndkUnionType, container.size());
		for (int i : UnionType_alternatives) {
			node.addAlternatives(i);
		}
		apspecNodes.put(ba, node);
		return node;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.UpperBoundedWildcardType UpperBoundedWildcardType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public UpperBoundedWildcardType createUpperBoundedWildcardType(int WildcardType_bound) {
		ByteArray ba = new ByteArray();
		ba.append(NodeKind.ndkUpperBoundedWildcardType.ordinal());
		ba.append(WildcardType_bound);

		Base b = apspecNodes.get(ba);
		if (b != null) {
			return (UpperBoundedWildcardType)b;
		}

		UpperBoundedWildcardType node = (UpperBoundedWildcardType)createNode(NodeKind.ndkUpperBoundedWildcardType, container.size());
		if (WildcardType_bound != 0)
			node.setBound(WildcardType_bound);
		apspecNodes.put(ba, node);
		return node;
	}

	/**
	 * Creates a new {@link columbus.java.asg.type.VoidType VoidType} node, insert it into the container and return with it.
	 * @return Reference to the new node.
	 */
	public VoidType createVoidType() {
		if (apspecNodeVoidType == null) {
			apspecNodeVoidType = (VoidType)createNode(NodeKind.ndkVoidType, container.size());
		}
		return apspecNodeVoidType;
	}


	private Base createSimpleAPSpecNodeSafely(NodeKind ndk, int id) {
		Base node = container.get(id);
		if (node != null) {
			if (node.getNodeKind() != ndk) {
				throw new JavaException(logger.formatMessage("ex.java.Factory.Wrong_node_kind", id, node.getNodeKind(), ndk));
			}
		} else {
			node = createNode(ndk, id);
		}
		return node;
	}

	private void init() {
		int id = 10;

		apspecNodeVoidType = (VoidType)createSimpleAPSpecNodeSafely(NodeKind.ndkVoidType, id++);
		apspecNodeBooleanType = (BooleanType)createSimpleAPSpecNodeSafely(NodeKind.ndkBooleanType, id++);
		apspecNodeCharType = (CharType)createSimpleAPSpecNodeSafely(NodeKind.ndkCharType, id++);
		apspecNodeByteType = (ByteType)createSimpleAPSpecNodeSafely(NodeKind.ndkByteType, id++);
		apspecNodeShortType = (ShortType)createSimpleAPSpecNodeSafely(NodeKind.ndkShortType, id++);
		apspecNodeIntType = (IntType)createSimpleAPSpecNodeSafely(NodeKind.ndkIntType, id++);
		apspecNodeLongType = (LongType)createSimpleAPSpecNodeSafely(NodeKind.ndkLongType, id++);
		apspecNodeFloatType = (FloatType)createSimpleAPSpecNodeSafely(NodeKind.ndkFloatType, id++);
		apspecNodeDoubleType = (DoubleType)createSimpleAPSpecNodeSafely(NodeKind.ndkDoubleType, id++);

		apspecNodeNullType = (NullType)createSimpleAPSpecNodeSafely(NodeKind.ndkNullType, id++);
		apspecNodeNoType = (NoType)createSimpleAPSpecNodeSafely(NodeKind.ndkNoType, id++);
		apspecNodeErrorType = (ErrorType)createSimpleAPSpecNodeSafely(NodeKind.ndkErrorType, id++);
	}

}
