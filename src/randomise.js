
var bv = BrainVoyager;

var scriptObj  = new Object;

scriptObj.dialogFileName = "randomise.ui";
scriptObj.dialogAccessName = "PluginDialog";

scriptObj.initDlg = function(){
    dlg = this.PluginDialog;
    dlg.windowTitle = "Randomise GUI";
    dlg.designGroupBox.typeOfStudyComboBox.addItem("Custom");
    dlg.designGroupBox.typeOfStudyComboBox.addItem("One-Sample T-Test");
    dlg.designGroupBox.typeOfStudyComboBox.addItem("Two-Sample Unpaired T-Test");
    dlg.designGroupBox.typeOfStudyComboBox.addItem("Two-Sample Paired T-Test");
    dlg.designGroupBox.typeOfStudyComboBox.addItem("ANOVA: 1-factor 4-levels (Repeated Measures)");

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

    dlg.optionsGroupBox.statisticToUseComboBox.addItem("F");
    dlg.optionsGroupBox.statisticToUseComboBox.addItem("G");

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
        bv.SetPluginStringParameter("C", dlg.optionsGroupBox.tfceOptionsGroupBox.tfceCComboBox.currentText);
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

    //Setting parameters for FTests (if any)
    for(var i = 0; i < numberFTests; i++){
        for(var j = 0; j < numberContrasts; j++){
            var text = dlg.designGroupBox.fTestMatrixTableWidget.item(j,i).text();
            var variableName = "FTestMatrix"+i+""+j;
            bv.SetPluginStringParameter(variableName, text);
        }
    }

    //Setting statistic to use
    bv.SetPluginStringParameter("Statistic", dlg.optionsGroupBox.statisticToUseComboBox.currentText);

    //Setting plugin command
    bv.SetPluginStringParameter("Command", "Execute");

    //GO!!!
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

        dlg.optionsGroupBox.statisticToUseComboBox.setEnabled(false);

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

        if(currentStudy == "One-Sample T-Test"){
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

            //Setting proper statistic
            dlg.optionsGroupBox.statisticToUseComboBox.setCurrentText("F");

        }
        else if(currentStudy == "Two-Sample Unpaired T-Test"){
            dlg.optionsGroupBox.eeCheckBox.setChecked(true);
            this.addColumn();
            this.addColumn();
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

            //Setting proper statistic
            dlg.optionsGroupBox.statisticToUseComboBox.setCurrentText("F");

        }else if(currentStudy == "Two-Sample Paired T-Test"){
            dlg.optionsGroupBox.eeCheckBox.setChecked(true);
            this.addColumn();
            for(var i = 0; i < num_of_maps/2; i++){
                this.addColumn();
            }

            this.addContrast();
            this.addGroup();
            this.addGroup();

            //Filling the design matrix
            //First column
            for(var i = 0; i < num_of_maps/2; i++){
                var item1 = new QTableWidgetItem("1");
                dlg.designGroupBox.designMatrixTableWidget.setItem(i,0,item1);
            }
            for(var i = num_of_maps/2; i < num_of_maps; i++){
                var item1 = new QTableWidgetItem("-1");
                dlg.designGroupBox.designMatrixTableWidget.setItem(i,0,item1);
            }

            //Other columns
            for(var j = 1; j < num_of_maps/2 + 1; j++){
                for(var i = 0; i < num_of_maps/2; i++){
                    if(j == i+1){
                        var item1 = new QTableWidgetItem("1");
                        dlg.designGroupBox.designMatrixTableWidget.setItem(i,j,item1);
                    }else{
                        var item1 = new QTableWidgetItem("0");
                        dlg.designGroupBox.designMatrixTableWidget.setItem(i,j,item1);
                    }
                }
                for(var i = num_of_maps/2; i < num_of_maps; i++){
                    var k = i - num_of_maps/2;
                    if(j == k+1){
                        var item1 = new QTableWidgetItem("1");
                        dlg.designGroupBox.designMatrixTableWidget.setItem(i,j,item1);
                    }else{
                        var item1 = new QTableWidgetItem("0");
                        dlg.designGroupBox.designMatrixTableWidget.setItem(i,j,item1);
                    }
                }
            }

            //Filling the group matrix
            for(var i = 0; i < num_of_maps; i++){
                var item1 = new QTableWidgetItem("-1");
                dlg.designGroupBox.groupMatrixTableWidget.setItem(i,0,item1);
            }
            var j = 1;
            for(var i = 0; i < num_of_maps/2; i++){
                var item1 = new QTableWidgetItem(""+j);
                var item2 = new QTableWidgetItem(""+j);
                dlg.designGroupBox.groupMatrixTableWidget.setItem(i,1,item1);
                dlg.designGroupBox.groupMatrixTableWidget.setItem(i+num_of_maps/2,1,item2);
                j = j + 1;
            }

            //Filling the contrast matrix
            var item1 = new QTableWidgetItem("1");
            dlg.designGroupBox.contrastMatrixTableWidget.setItem(0,0,item1);
            for(var i = 1; i < num_of_maps+1; i++){
                var item1 = new QTableWidgetItem("0");
                dlg.designGroupBox.contrastMatrixTableWidget.setItem(0,i,item1);
            }

            //Setting proper statistic
            dlg.optionsGroupBox.statisticToUseComboBox.setCurrentText("F");

        }else if(currentStudy == "ANOVA: 1-factor 4-levels (Repeated Measures)"){
            var num_subjects = num_of_maps/4;
            for(var i = 0; i < num_subjects; i++){
                this.addColumn();
            }
            this.addColumn();
            this.addColumn();
            this.addColumn();

            this.addContrast();
            this.addContrast();
            this.addContrast();

            this.addFTest();
            this.addGroup();
            this.addGroup();

            for(var i = 0; i < num_subjects; i++){
                var firstRowSubjI = i*4;
                for(var j = 0; j < 4; j++){
                    var item1 = new QTableWidgetItem("1");
                    dlg.designGroupBox.designMatrixTableWidget.setItem(j+firstRowSubjI,i,item1);
                }
            }

            //Setting proper statistic
            dlg.optionsGroupBox.statisticToUseComboBox.setCurrentText("F");
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

        dlg.optionsGroupBox.statisticToUseComboBox.setEnabled(true);
    }
}

returnScriptObj = function(){
    return scriptObj;
}

returnScriptObj();
