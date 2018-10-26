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
		
	-- useful predefineds:
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

	-- use several projects for lib(backend), ui and tests. Combine these in a subdir-.pro:
		TEMPLATE = subdirs
		SUBDIRS += \
			myapp-ui \
			myapp-lib \
			myapp-tests

## Qt QML CheatSheet
	-- # Additional import path used to resolve QML modules in Qt Creator's code model
		QML_IMPORT_PATH = $$PWD
	-- You need exchangeable content? Use StackView(has history: .pop/.push/.replace):
		StackView {
			id: contentFrame
			clip: true
			InitialItem: Qt.resolvedUrl("qrc:/splashview.qml")
			Component.onCompleted: contentFrame.replace("qrc:/views/DashboardView.qml");
			//or Button { onClicked: masterController.ui_navigationController.go()
			Connections {
				target: masterController.ui_navigationController
				onGo: contentFrame.replace("qrc:/views/CreateClientView.qml")
		Usage: 
			onClicked:
				contentFrame.push("qrc:/SecondView.qml", {attr1: myattr1, attr2: myattr2})

	-- Use always relative positioning (to reach a responsive UI), with anchors, like
		anchors.centerIn: parent
		anchors.fill: parent
		anchors.top: parent.top
		anchors {
			top: parent.top
			left: parent.left
			margins: 20
			verticalCenterOffset: 20
		}
	-- use C++ Controller (parent: QObject):
		Q_OBJECT
		Q_PROPERTY(QString ui_msg MEMBER msg CONSTANT)	#macros: MEMBER,READ,WRITE,NOTIFY propChanged
		Q_PROPERTY( my::controllers::NavigationController* ui_navigationController READ navigationController CONSTANT )
		Q_PROPERTY(QQmlListProperty< ...
		const QString& msg() const;
		signals:
			void onGo();
			void propChanged();
		# eg. in main.cpp:
		qmlRegisterType<my::controllers::MasterController>("MyApp", 1, 0, "MasterController");	# naviCtrl similarly
		#or, with interfaces:
		qmlRegisterUncreatableType<my::controllers::IMasterController>("MyApp", 1, 0, "IMasterController", "Interface");
		engine.rootContext()->setContextProperty("masterController", &masterController);
		# import in QML
		import MyApp 1.0
	-- use centralized Style.qml:
		pragma Singleton
		import QtQuick 2.9
		Item {
			readonly property color clrBkg: "#f4c842"
		}
		//needs qmldir file (include it to your .qrc):
		module assets
		singleton Style 1.0 Style.qml
		//import it in your .qml files with
		import assets 1.0
		//adjust import path:
		engine.addImportPath("qrc:/");		//better than edit build settings -> set QML2_IMPORT_PATH
		//use the centralized style:
		import assets 1.0
		color: Style.clrBkg
	-- use [awesome](http://fontawesome.io/) fonts & icons! assets.qrc:
		Item {
			property alias fontAwesome: fontAwesomeLoader.name
			readonly property color clrBkg: "#efefef"
			FontLoader {
				id: fontAwesomeLoader
				source: "qrc:/assets/fontawesome.ttf"
		usage:
			Row {
				Text {
					font {
						family: Style.fontAwesome
						pixelSize: 42
					}
					color: "#ffffff"
					text: "\uf015"				#house icon of awesomefonts
				}
				Text {
					color: "#ffffff"
					text: "Home"
					verticalAlignment: Text.AlignVCenter
				}
	-- build components, eg NaviBtn.qml:
		Item {
			property alias iconCharacter: textIcon.text
			property alias description: textDescription.text
			signal NaviBtnClicked()
			width: ...
			Row {
				Text {
					id: textIcon
					text: "..."
		//define components in a qmldir file
		module components
		NaviBtn 1.0 NaviBtn.qml
		//usage:
		import components 1.0
		NaviBtn {
			iconCharacter: "\uf0c9"
			onNaviBtnClicked: masterController.ui_navigationController.go();
	-- use states:
		states: [
			State {
				name: "hover"
				PropertyChanges {
					target: background
					color: hoverColour		#whereby: property color hoverColour: Style.colourNavigationBarBackground
					color: Qt.darker(Style.colourCommandBarBackground)
					
		Usage:
			MouseArea {
				anchors.fill: parent
				cursorShape: Qt.PointingHandCursor
				hoverEnabled: true
				onEntered: background.state = "hover"
				onExited: background.state = ""
				onClicked: NaviBtnClicked()

	-- List alternative: use Repeater:
		Repeater {
			delegate: CommandButton {
				command: modelData
	
	-- Load QML content dynamically, with Loader:
		MyPanel.qml:
		Item {
			property alias contentComponent: contentLoader.sourceComponent
			# Header...
			Loader {
				id: contentLoader
				anchors {
					...
		Usage:
		MyPanel {
			# set Header attribs...
			contentComponent:
				Column {
					...

	-- Access Qt.<globalScope> functionality in QML this way:
		Text { text: Qt.formatDateTime(rssItem.ui_pubDate, "ddd, d MMM yyyy @ h:mm ap")
		Qt.openUrlExternally(rssItem.ui_link);
		Qt.AlignVCenter
		
	-- Alternative to ListView { delegate: my model: my :
		Flow { Repeater { delegate: my model: my

## QT C++ Hints
	-- instead of plain pointer, use QScopedPointer<CLASSNAME>
	-- with CONFIG += c++14, use lambdas:
		QObject::connect(&myobj, &myclass::valueChanged, [&isCalled](){
			isCalled = true;
		});
	-- QtTest:
		useful macros: Q_SLOTS, QVERIFY/2, QCOMPARE; QVERIFY_EXCEPTION_THROWN, QTEST_APPLESS_MAIN
		use XML configuration for test suite: <testsuite ..<testcase ...
		use QSignalSpy:
			QSignalSpy valueChangedSpy(&myobj, &myclass::valueChanged);
			myobj.setValue(99);
			QCOMPARE(valueChangedSpy.count(), 1);
	-- packaging:
		MacOS: macdeployqt -qmldir -libpath
			if manually, command line tools helping;
				otool (~ldd on linux), install_name_tool -change -id
		Linux: export PATH=<Qt-Path>/5.9.1/gcc_64/bin/:$PATH linuxdeployqt -qmldir -appimage
		Windows: qindeployqt --qmldir --compiler-runtime

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
