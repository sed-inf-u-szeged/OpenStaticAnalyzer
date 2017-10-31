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

package columbus.java.asg;

import columbus.ColumbusException;

/**
 * Exception class for the 'java' graph.
 */
@SuppressWarnings("serial")
public class JavaException extends ColumbusException {

	/**
	 * Constructor.
	 */
	public JavaException() {
		super();
	}

	/**
	 * Constructor.
	 * @param message The detail message.
	 */
	public JavaException(String message) {
		super(message);
	}

	/**
	 * Constructor.
	 * @param message The detail message.
	 * @param cause   The cause of the exception.
	 */
	public JavaException(String message, Throwable cause) {
		super(message, cause);
	}

	/**
	 * Constructor.
	 * @param cause The cause of the exception.
	 */
	public JavaException(Throwable cause) {
		super(cause);
	}

}
