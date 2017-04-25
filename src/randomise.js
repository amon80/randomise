
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

    var num_of_maps = bv.GetPluginIntParameter("NumOfMaps");

    for(i = 0; i < num_of_maps; i++){
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

    dlg.buttonBox.accepted.connect(this, this.collectDataAndFire);
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
    if(dlg.optionsGroupBox.tfceCheckBox.checked)
        bv.SetPluginIntParameter("UseTfce",  1);
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

    //TODO: Set all the actual data

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
        }
        else if(currentStudy == "Two-Sample Unpaired T-Test"){
            dlg.optionsGroupBox.eeCheckBox.setChecked(true);
            this.addColumn();
            this.addColumn();
            this.addContrast();
            this.addContrast();
            this.addGroup();
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
