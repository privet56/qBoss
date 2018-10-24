# Desktop App: qBoss

## controls deployment on Java App Servers (like JBoss)

GUI :
#####

![qboss_ui](https://raw.githubusercontent.com/privet56/qBoss/master/qboss_ui.gif)
![qboss_ui2](https://raw.githubusercontent.com/privet56/qBoss/master/qboss_ui.2.gif)

//TODO:
// 1) Tab: DB Search
// 2) Tab: Performance Graph

## Qt .pro CheatSheet
	-- message:
		# PWD = project working directory
		message(my project dir: $${PWD})
		!build_pass:message(my project dir: $${PWD})
		
	-- predefineds:
		PLATFORM_WIN / PLATFORM_OSX / PLATFORM_LINUX
		COMPILER_GCC / COMPILER_MSVC2017 / COMPILER_CLANG
		PROCESSOR_x64 / PROCESSOR_x86
		BUILD_DEBUG

	-- use predefined macros to set variables:
		platform_path = unknown-platform
		PLATFORM_WIN {
			platform_path = windows
		}
		win32 {
			CONFIG += PLATFORM_WIN
			message(PLATFORM_WIN)
			win32-g++ {
				CONFIG += COMPILER_GCC
				message(COMPILER_GCC)
			}
			!contains(QT_ARCH, x86_64){
				QMAKE_TARGET.arch = x86
			} else {
				QMAKE_TARGET.arch = x86_64
			}
		}
		
	-- set above defines in an includeable .pri file:
		include(../qmake-target-platform.pri)
		
	-- build paths based on set variables:
		DESTDIR = $$PWD/../binaries/windows/gcc/x86/debug
		DESTINATION_PATH = $$platform_path/$$compiler_path/$$processor_path/$$build_path
		message(my-lib output dir: $${DESTDIR})
		LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -lmy-lib
		
	-- used paths at build time:
		DESTDIR / OBJECTS_DIR / MOC_DIR / RCC_DIR / UI_DIR

## Qt QML CheatSheet
	-- You need exchangeable content? Use StackView
		StackView {
			InitialItem: "qrc:/splashview.qml"
	-- Use always relative positioning, with anchors, like
		anchors.centerIn: parent
		anchors.fill: parent
		anchors.top: parent.top
		anchors {
			top: parent.top
			left: parent.left
			margins: 20
			verticalCenterOffset: 20
		}


## git CheatSheet
	--- global settings ---
	$ git config --global user.name "privet"
	$ git config --global user.email privet56@hotmail.com
	--- init repo ---
	$ git init
	$ git config user.name "privet"
	$ git config user.email privet56@hotmail.com
	//TODO: create .gitignore
	$ git add .					//doesn't handle deleted files!
	$ git add -u .				//-u handles deleted files only!
	$ git commit -m "initial commit"
	//create repo on github within your browser
	$ git remote add origin https://github.com/privet56/qBoss.git
	$ git remote -v
	$ git pull origin master --allow-unrelated-histories
	$ git push origin master
	--- further commands ---
	$ git add .
	$ git commit -m "new feature"
	$ git push origin master
