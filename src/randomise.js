
var bv = BrainVoyager;

var scriptObj  = new Object;

scriptObj.dialogFileName = "randomise.ui";
scriptObj.dialogAccessName = "PluginDialog";

scriptObj.initDlg = function(){
    dlg = this.PluginDialog;
    dlg.windowTitle = "Randomise GUI";
    dlg.designGroupBox.typeOfStudyComboBox.addItem("Custom");
    dlg.designGroupBox.typeOfStudyComboBox.addItem("Mean Effect");
    dlg.designGroupBox.typeOfStudyComboBox.addItem("Two-Sample Unpaired T-Test");
    //TODO:Add other studies

    bv.SetPluginStringParameter("Command", "GetNumOfMaps");
    bv.ExecutePlugin();

    num_of_maps = bv.GetPluginIntParameter("NumOfMaps");

    for(var i = 0; i < num_of_maps; i++){
        dlg.designGroupBox.designMatrixTableWidget.insertRow(i);
        dlg.designGroupBox.groupMatrixTableWidget.insertRow(i);
    }

    dlg.designGroupBox.typeOfStudyComboBox.currentTextChanged.connect(this, this.onChangeStudy);

    dlg.designGroupBox.designMatrixAddColumnButton.clicked.connect(this, this.addColumn);
    dlg.designGroupBox.designMatrixRemoveColumnButton.clicked.connect(this, this.removeColumn);

    dlg.designGroupBox.groupMatrixAddGroupButton.clicked.connect(this, this.addGroup);
    dlg.designGroupBox.groupMatrixRemoveGroupButton.clicked.connect(this, this.removeGroup);

    dlg.designGroupBox.contrastMatrixAddContrastButton.clicked.connect(this, this.addContrast);
    dlg.designGroupBox.contrastMatrixRemoveContrastButton.clicked.connect(this, this.removeContrast);

    dlg.designGroupBox.fTestMatrixAddFTestButton.clicked.connect(this, this.addFTest);
    dlg.designGroupBox.fTestMatrixRemoveFTestButton.clicked.connect(this, this.removeFTest);

    dlg.optionsGroupBox.tfceOptionsGroupBox.tfceCComboBox.addItem("6 connectivity");
    dlg.optionsGroupBox.tfceOptionsGroupBox.tfceCComboBox.addItem("18 connectivity");
    dlg.optionsGroupBox.tfceOptionsGroupBox.tfceCComboBox.addItem("26 connectivity");

    dlg.optionsGroupBox.tfceCheckBox.toggled.connect(this, this.enableTfceOptions);

    dlg.buttonBox.accepted.connect(this, this.collectDataAndFire);
}

scriptObj.enableTfceOptions = function(){
    var t = dlg.optionsGroupBox.tfceCheckBox.checked;
    if(t){
        dlg.optionsGroupBox.tfceOptionsGroupBox.tfceESpinBox.setEnabled(true);
        dlg.optionsGroupBox.tfceOptionsGroupBox.tfceHSpinBox.setEnabled(true);
        dlg.optionsGroupBox.tfceOptionsGroupBox.tfceDhSpinBox.setEnabled(true);
        dlg.optionsGroupBox.tfceOptionsGroupBox.tfceCComboBox.setEnabled(true);
    }else{
        dlg.optionsGroupBox.tfceOptionsGroupBox.tfceESpinBox.setEnabled(false);
        dlg.optionsGroupBox.tfceOptionsGroupBox.tfceHSpinBox.setEnabled(false);
        dlg.optionsGroupBox.tfceOptionsGroupBox.tfceDhSpinBox.setEnabled(false);
        dlg.optionsGroupBox.tfceOptionsGroupBox.tfceCComboBox.setEnabled(false);
    }
}


scriptObj.addColumn = function(){
    dlg.designGroupBox.designMatrixTableWidget.insertColumn(dlg.designGroupBox.designMatrixTableWidget.columnCount);
    dlg.designGroupBox.contrastMatrixTableWidget.insertColumn(dlg.designGroupBox.contrastMatrixTableWidget.columnCount);
}

scriptObj.removeColumn = function(){
    dlg.designGroupBox.designMatrixTableWidget.removeColumn(dlg.designGroupBox.designMatrixTableWidget.columnCount-1);
    dlg.designGroupBox.contrastMatrixTableWidget.removeColumn(dlg.designGroupBox.contrastMatrixTableWidget.columnCount-1);
}

scriptObj.addGroup = function(){
    dlg.designGroupBox.groupMatrixTableWidget.insertColumn(dlg.designGroupBox.groupMatrixTableWidget.columnCount);
}

scriptObj.removeGroup = function(){
    dlg.designGroupBox.groupMatrixTableWidget.removeColumn(dlg.designGroupBox.groupMatrixTableWidget.columnCount-1);
}

scriptObj.addContrast = function(){
    dlg.designGroupBox.contrastMatrixTableWidget.insertRow(dlg.designGroupBox.contrastMatrixTableWidget.rowCount);
    dlg.designGroupBox.fTestMatrixTableWidget.insertRow(dlg.designGroupBox.fTestMatrixTableWidget.rowCount);
}

scriptObj.removeContrast =  function(){
    dlg.designGroupBox.contrastMatrixTableWidget.removeRow(dlg.designGroupBox.contrastMatrixTableWidget.rowCount-1);
    dlg.designGroupBox.fTestMatrixTableWidget.removeRow(dlg.designGroupBox.fTestMatrixTableWidget.rowCount-1);
}

scriptObj.addFTest = function(){
    dlg.designGroupBox.fTestMatrixTableWidget.insertColumn(dlg.designGroupBox.fTestMatrixTableWidget.columnCount);
}

scriptObj.removeFTest =  function(){
    dlg.designGroupBox.fTestMatrixTableWidget.removeColumn(dlg.designGroupBox.fTestMatrixTableWidget.columnCount-1);
}

scriptObj.collectDataAndFire = function(){
    bv.SetPluginIntParameter("MaxPermutations",  dlg.optionsGroupBox.maxNumPermutationsSpinbox.value);
    bv.SetPluginFloatParameter("Alpha",  dlg.optionsGroupBox.desiredAlphaSpinBox.value);
    if(dlg.optionsGroupBox.tfceCheckBox.checked){
        bv.SetPluginIntParameter("UseTfce", 1);
        bv.SetPluginFloatParameter("H", dlg.optionsGroupBox.tfceOptionsGroupBox.tfceHSpinBox.value);
        bv.SetPluginFloatParameter("E", dlg.optionsGroupBox.tfceOptionsGroupBox.tfceESpinBox.value);
        bv.SetPluginFloatParameter("dh", dlg.optionsGroupBox.tfceOptionsGroupBox.tfceDhSpinBox.value);
        var conn = dlg.optionsGroupBox.tfceOptionsGroupBox.tfceCComboBox.currentText;
        bv.PrintToLog(conn);
        bv.SetPluginStringParameter("C", conn);

    }
    else
        bv.SetPluginIntParameter("UseTfce",  0);
    if(dlg.optionsGroupBox.eeCheckBox.checked)
        bv.SetPluginIntParameter("EE",  1);
    else
        bv.SetPluginIntParameter("EE",  0);
    if(dlg.optionsGroupBox.iseCheckBox.checked)
        bv.SetPluginIntParameter("ISE",  1);
    else
        bv.SetPluginIntParameter("ISE",  0);

    var numberContrasts = dlg.designGroupBox.contrastMatrixTableWidget.rowCount;
    var numberRegressors = dlg.designGroupBox.designMatrixTableWidget.columnCount;
    var numberFTests = dlg.designGroupBox.fTestMatrixTableWidget.columnCount;
    var numberGroupLayers = dlg.designGroupBox.groupMatrixTableWidget.columnCount;

    bv.SetPluginIntParameter("NumberOfContrasts", numberContrasts);
    bv.SetPluginIntParameter("NumberOfRegressors", numberRegressors);
    bv.SetPluginIntParameter("NumberOfFTests", numberFTests);
    bv.SetPluginIntParameter("NumberOfGroupLayers", numberGroupLayers);

    //Setting parameters for the design matrix
    for(var i = 0; i < num_of_maps; i++){
        for(var j = 0; j < numberRegressors; j++){
            var text = dlg.designGroupBox.designMatrixTableWidget.item(i,j).text();
            var variableName = "DesignMatrix"+i+""+j;
            bv.SetPluginStringParameter(variableName, text);
        }
    }

    //Setting parameters for the contrast matrix
    for(var i = 0; i < numberContrasts; i++){
        for(var j = 0; j < numberRegressors; j++){
            var text = dlg.designGroupBox.contrastMatrixTableWidget.item(i,j).text();
            var variableName = "ContrastMatrix"+i+""+j;
            bv.SetPluginStringParameter(variableName, text);
        }
    }

    //Setting parameters for the group matrix
    for(var i = 0; i < num_of_maps; i++){
        for(var j = 0; j < numberGroupLayers; j++){
            var text = dlg.designGroupBox.groupMatrixTableWidget.item(i,j).text();
            var variableName = "GroupMatrix"+i+""+j;
            bv.SetPluginStringParameter(variableName, text);
        }
    }

    //TODO:Set parameters for FTest

    bv.SetPluginStringParameter("Command", "Execute");
    bv.ExecutePlugin();
}


scriptObj.onChangeStudy = function(){
    var currentStudy = dlg.designGroupBox.typeOfStudyComboBox.currentText;
    if(currentStudy != "Custom"){
        dlg.designGroupBox.designMatrixAddColumnButton.setEnabled(false);
        dlg.designGroupBox.designMatrixRemoveColumnButton.setEnabled(false);

        dlg.designGroupBox.groupMatrixAddGroupButton.setEnabled(false);
        dlg.designGroupBox.groupMatrixRemoveGroupButton.setEnabled(false);

        dlg.designGroupBox.contrastMatrixAddContrastButton.setEnabled(false);
        dlg.designGroupBox.contrastMatrixRemoveContrastButton.setEnabled(false);

        dlg.designGroupBox.fTestMatrixAddFTestButton.setEnabled(false);
        dlg.designGroupBox.fTestMatrixRemoveFTestButton.setEnabled(false);

        dlg.optionsGroupBox.eeCheckBox.setEnabled(false);
        dlg.optionsGroupBox.iseCheckBox.setEnabled(false);
        dlg.optionsGroupBox.eeCheckBox.setChecked(false);
        dlg.optionsGroupBox.iseCheckBox.setChecked(false);

        while(dlg.designGroupBox.contrastMatrixTableWidget.rowCount != 0){
            this.removeContrast();
        }
        while(dlg.designGroupBox.designMatrixTableWidget.columnCount != 0){
            this.removeColumn();
        }
        while(dlg.designGroupBox.fTestMatrixTableWidget.columnCount != 0){
            this.removeFTest();
        }
        while(dlg.designGroupBox.groupMatrixTableWidget.columnCount != 0){
            this.removeGroup();
        }

        if(currentStudy == "Mean Effect"){
            dlg.optionsGroupBox.iseCheckBox.setChecked(true);
            this.addColumn();
            this.addContrast();
            this.addGroup();
            //Filling Design Matrix and Group Matrix
            for(i = 0; i < num_of_maps; i++){
                var item1 = new QTableWidgetItem("1");
                dlg.designGroupBox.designMatrixTableWidget.setItem(i,0,item1);
                var item1 = new QTableWidgetItem("1");
                dlg.designGroupBox.groupMatrixTableWidget.setItem(i,0,item1);
            }
            //Filling the contrast matrix
            var item1 = new QTableWidgetItem("1");
            dlg.designGroupBox.contrastMatrixTableWidget.setItem(0,0,item1);
        }
        else if(currentStudy == "Two-Sample Unpaired T-Test"){
            dlg.optionsGroupBox.eeCheckBox.setChecked(true);
            this.addColumn();
            this.addColumn();
            this.addContrast();
            this.addContrast();
            this.addGroup();

            //Filling the design matrix
            for(var i = 0; i < num_of_maps/2; i++){
                var item1 = new QTableWidgetItem("1");
                var item0 = new QTableWidgetItem("0");
                dlg.designGroupBox.designMatrixTableWidget.setItem(i,0,item1);
                dlg.designGroupBox.designMatrixTableWidget.setItem(i,1,item0);
            }
            for(var i = num_of_maps/2; i < num_of_maps; i++){
                var item1 = new QTableWidgetItem("1");
                var item0 = new QTableWidgetItem("0");
                dlg.designGroupBox.designMatrixTableWidget.setItem(i,0,item0);
                dlg.designGroupBox.designMatrixTableWidget.setItem(i,1,item1);
            }

            //Filling the group matrix
            for(var i = 0; i < num_of_maps; i++){
                var item1 = new QTableWidgetItem("1");
                dlg.designGroupBox.groupMatrixTableWidget.setItem(i,0,item1);
            }

            //Filling the contrast matrix
            var item1 = new QTableWidgetItem("1");
            dlg.designGroupBox.contrastMatrixTableWidget.setItem(0,0,item1);
            var item1 = new QTableWidgetItem("-1");
            dlg.designGroupBox.contrastMatrixTableWidget.setItem(0,1,item1);
            var item1 = new QTableWidgetItem("-1");
            dlg.designGroupBox.contrastMatrixTableWidget.setItem(1,0,item1);
            var item1 = new QTableWidgetItem("1");
            dlg.designGroupBox.contrastMatrixTableWidget.setItem(1,1,item1);
        }
    }else{
        dlg.designGroupBox.designMatrixAddColumnButton.setEnabled(true);
        dlg.designGroupBox.designMatrixRemoveColumnButton.setEnabled(true);

        dlg.designGroupBox.groupMatrixAddGroupButton.setEnabled(true);
        dlg.designGroupBox.groupMatrixRemoveGroupButton.setEnabled(true);

        dlg.designGroupBox.contrastMatrixAddContrastButton.setEnabled(true);
        dlg.designGroupBox.contrastMatrixRemoveContrastButton.setEnabled(true);

        dlg.designGroupBox.fTestMatrixAddFTestButton.setEnabled(true);
        dlg.designGroupBox.fTestMatrixRemoveFTestButton.setEnabled(true);

        dlg.optionsGroupBox.eeCheckBox.setEnabled(true);
        dlg.optionsGroupBox.iseCheckBox.setEnabled(true);
    }
}

returnScriptObj = function(){
    return scriptObj;
}

returnScriptObj();
