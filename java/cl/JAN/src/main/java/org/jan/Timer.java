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

package org.jan;

import java.lang.management.ManagementFactory;
import java.lang.management.ThreadMXBean;

/*
 * Only works properly for single threaded tasks, can be extended for multiple threads
 */

public class Timer {
	// time spent running the application's own code.
	private long startUserTime;
	private long stopUserTime;

	// the time spent running OS code on behalf of the application (such as for I/O).
	private long startSystemTime;
	private long stopSystemTime;
	
	// User time plus system time. It's the total time spent using a CPU for the application.
	private long startCpuTime;
	private long stopCpuTime;
	
	private String info;
	
	public Timer(String info) {
		this.info = info;
	}

	public void start() {
		startUserTime = getCurrentUserTime();
		startSystemTime = getCurrentSystemTime();
		startCpuTime = getCurrentCpuTime();
	}

	public void stop() {
		stopUserTime = getCurrentUserTime();
		stopSystemTime = getCurrentSystemTime();
		stopCpuTime = getCurrentCpuTime();
	}

	public long getTotalUserTime() {
		return (stopUserTime - startUserTime)/1000000;
	}

	public long getTotalSystemTime() {
		return (stopSystemTime - startSystemTime)/1000000;
	}
	
	public long getTotalCpuTime() {
		return (stopCpuTime - startCpuTime)/1000000;
	}
	
	public String getInfo() {
		return info;
	}

	// Get user time in nanoseconds.
	private long getCurrentUserTime() {
		ThreadMXBean bean = ManagementFactory.getThreadMXBean();
		return bean.isCurrentThreadCpuTimeSupported() ? bean.getCurrentThreadUserTime() : 0L;
	}

	// Get system time in nanoseconds.
	private long getCurrentSystemTime() {
		ThreadMXBean bean = ManagementFactory.getThreadMXBean();
		return bean.isCurrentThreadCpuTimeSupported() ? (bean.getCurrentThreadCpuTime() - bean
				.getCurrentThreadUserTime()) : 0L;
	}
	
	// Get CPU time in nanoseconds.
	private long getCurrentCpuTime() {
		ThreadMXBean bean = ManagementFactory.getThreadMXBean();
		return bean.isCurrentThreadCpuTimeSupported() ? bean.getCurrentThreadCpuTime() : 0L;
	}

}
