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

package columbus.logger;

import java.util.HashMap;
import java.util.ResourceBundle;

import org.slf4j.LoggerFactory;
import org.slf4j.helpers.FormattingTuple;
import org.slf4j.helpers.MessageFormatter;

import ch.qos.logback.classic.Level;
import ch.qos.logback.classic.Logger;
import ch.qos.logback.classic.LoggerContext;
import ch.qos.logback.classic.joran.JoranConfigurator;
import ch.qos.logback.core.joran.spi.JoranException;
import ch.qos.logback.core.util.StatusPrinter;

public class LoggerHandler {

	private static class LoggerData {
		LoggerData(ResourceBundle rb) {
			this.rb = rb;
		}

		volatile int warnMessages = 0;
		volatile int errorMessages = 0;
		final ResourceBundle rb;
	}

	private static HashMap<String, LoggerData> dataMap = new HashMap<>();
	private LoggerData data;

	private Logger logger;

	public LoggerHandler(Class<?> clazz, String path) {
		logger = (Logger) LoggerFactory.getLogger(clazz);
		data = dataMap.get(path);
		if (data == null) {
			data = new LoggerData(ResourceBundle.getBundle(path));
			dataMap.put(path, data);
		}
	}

	public static void setMessageLevel(int level) {
		Logger root = (Logger) LoggerFactory.getLogger(Logger.ROOT_LOGGER_NAME);
		switch (level) {
		case 0:
			root.setLevel(Level.OFF);
			break;
		case 1:
			root.setLevel(Level.ERROR);
			break;
		case 2:
			root.setLevel(Level.WARN);
			break;
		case 3:
			root.setLevel(Level.INFO);
			break;
		case 4:
			root.setLevel(Level.DEBUG);
			break;
		case 5:
			root.setLevel(Level.TRACE);
			break;
		case 6:
			root.setLevel(Level.ALL);
			break;
		default:
			root.setLevel(Level.INFO);
		}
	}

	public static void initLogback(String logbackXml) {
		// assume SLF4J is bound to logback in the current environment
		LoggerContext context = (LoggerContext) LoggerFactory.getILoggerFactory();
		try {
			JoranConfigurator configurator = new JoranConfigurator();
			configurator.setContext(context);
			// Call context.reset() to clear any previous configuration, e.g. default
			// configuration. For multi-step configuration, omit calling context.reset().
			context.reset();
			configurator.doConfigure(logbackXml);
		} catch (JoranException je) {
			// StatusPrinter will handle this
		}
		StatusPrinter.printInCaseOfErrorsOrWarnings(context);
	}

	public String formatMessage(String key, Object... args) {
		String ret = "";
		try {
			FormattingTuple tuple = MessageFormatter.arrayFormat(data.rb.getString(key), args);
			ret = tuple.getMessage();
		} catch (Exception e) {
			logger.error(e.toString());
			data.errorMessages++;
		}
		return ret;
	}

	public int getWarnMessages() {
		return data.warnMessages;
	}

	public int getErrorMessages() {
		return data.errorMessages;
	}

	public static int getTotalWarnMessages() {
		int warnMessages = 0;
		for (LoggerData data : dataMap.values()) {
			warnMessages += data.warnMessages;
		}
		return warnMessages;
	}

	public static int getTotalErrorMessages() {
		int errorMessages = 0;
		for (LoggerData data : dataMap.values()) {
			errorMessages += data.errorMessages;
		}
		return errorMessages;
	}

	public void error(String key, Object... args) {
		if (logger.isErrorEnabled()) {
			try {
				logger.error(data.rb.getString(key), args);
			} catch (Exception e) {
				logger.error(e.toString());
				data.errorMessages++;
			}
		}
		data.errorMessages++;
	}

	public void warn(String key, Object... args) {
		if (logger.isWarnEnabled()) {
			try {
				logger.warn(data.rb.getString(key), args);
			} catch (Exception e) {
				logger.error(e.toString());
				data.errorMessages++;
			}
		}
		data.warnMessages++;
	}

	public void info(String key, Object... args) {
		if (logger.isInfoEnabled()) {
			try {
				logger.info(data.rb.getString(key), args);
			} catch (Exception e) {
				logger.error(e.toString());
				data.errorMessages++;
			}
		}
	}

	public void infoMsg(String msg, Object... args) {
		if (logger.isInfoEnabled()) {
			try {
				logger.info(msg, args);
			} catch (Exception e) {
				logger.error(e.toString());
				data.errorMessages++;
			}
		}
	}

	public void debug(String key, Object... args) {
		if (logger.isDebugEnabled()) {
			try {
				logger.debug(data.rb.getString(key), args);
			} catch (Exception e) {
				logger.error(e.toString());
				data.errorMessages++;
			}
		}
	}

	public boolean isInfoEnabled() {
		return logger.isInfoEnabled();
	}

	public boolean isDebugEnabled() {
		return logger.isDebugEnabled();
	}

}
