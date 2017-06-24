
var bv = BrainVoyager;

var scriptObj  = new Object;

scriptObj.dialogFileName = "randomise.ui";
scriptObj.dialogAccessName = "PluginDialog";

function addEntryToTable(table, row, column, value){
    var item = new QTableWidgetItem(value);
    table.setItem(row,column,item);
}

scriptObj.initDlg = function(){
    dlg = this.PluginDialog;
    dlg.windowTitle = "Randomise GUI";

    //Shortening names
    designMatrix = dlg.designGroupBox.designMatrixTableWidget;
    treeMatrix = dlg.designGroupBox.groupMatrixTableWidget;
    contrastMatrix = dlg.designGroupBox.contrastMatrixTableWidget;
    ftestMatrix = dlg.designGroupBox.fTestMatrixTableWidget;
    studies = dlg.designGroupBox.typeOfStudyComboBox;

    studies.addItem("Custom");
    studies.addItem("One-Sample T-Test");
    studies.addItem("Two-Sample Unpaired T-Test");
    studies.addItem("Two-Sample Paired T-Test");
    studies.addItem("ANOVA: 1 factor 4 levels (Repeated measures)");

    bv.SetPluginStringParameter("Command", "GetNumOfMaps");
    bv.ExecutePlugin();

    num_of_maps = bv.GetPluginIntParameter("NumOfMaps");

    for(var i = 0; i < num_of_maps; i++){
        designMatrix.insertRow(i);
        treeMatrix.insertRow(i);
    }

    studies.currentTextChanged.connect(this, this.onChangeStudy);

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

    dlg.optionsGroupBox.statisticToUseComboBox.addItem("T");
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
    designMatrix.insertColumn(designMatrix.columnCount);
    contrastMatrix.insertColumn(contrastMatrix.columnCount);
}

scriptObj.removeColumn = function(){
    designMatrix.removeColumn(designMatrix.columnCount-1);
    contrastMatrix.removeColumn(contrastMatrix.columnCount-1);
}

scriptObj.addGroup = function(){
    treeMatrix.insertColumn(treeMatrix.columnCount);
}

scriptObj.removeGroup = function(){
    treeMatrix.removeColumn(treeMatrix.columnCount-1);
}

scriptObj.addContrast = function(){
    contrastMatrix.insertRow(contrastMatrix.rowCount);
    ftestMatrix.insertRow(ftestMatrix.rowCount);
}

scriptObj.removeContrast =  function(){
    contrastMatrix.removeRow(contrastMatrix.rowCount-1);
    ftestMatrix.removeRow(ftestMatrix.rowCount-1);
}

scriptObj.addFTest = function(){
    ftestMatrix.insertColumn(ftestMatrix.columnCount);
}

scriptObj.removeFTest =  function(){
    ftestMatrix.removeColumn(ftestMatrix.columnCount-1);
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

    var numberContrasts = contrastMatrix.rowCount;
    var numberRegressors = designMatrix.columnCount;
    var numberFTests = ftestMatrix.columnCount;
    var numberGroupLayers = treeMatrix.columnCount;

    bv.SetPluginIntParameter("NumberOfContrasts", numberContrasts);
    bv.SetPluginIntParameter("NumberOfRegressors", numberRegressors);
    bv.SetPluginIntParameter("NumberOfFTests", numberFTests);
    bv.SetPluginIntParameter("NumberOfGroupLayers", numberGroupLayers);

    //Setting parameters for the design matrix
    for(var i = 0; i < num_of_maps; i++){
        for(var j = 0; j < numberRegressors; j++){
            var text = designMatrix.item(i,j).text();
            var variableName = "DesignMatrix"+i+""+j;
            bv.SetPluginStringParameter(variableName, text);
        }
    }

    //Setting parameters for the contrast matrix
    for(var i = 0; i < numberContrasts; i++){
        for(var j = 0; j < numberRegressors; j++){
            var text = contrastMatrix.item(i,j).text();
            var variableName = "ContrastMatrix"+i+""+j;
            bv.SetPluginStringParameter(variableName, text);
        }
    }

    //Setting parameters for the group matrix
    for(var i = 0; i < num_of_maps; i++){
        for(var j = 0; j < numberGroupLayers; j++){
            var text = treeMatrix.item(i,j).text();
            var variableName = "GroupMatrix"+i+""+j;
            bv.SetPluginStringParameter(variableName, text);
        }
    }

    //Setting parameters for FTests (if any)
    for(var i = 0; i < numberFTests; i++){
        for(var j = 0; j < numberContrasts; j++){
            var text = ftestMatrix.item(j,i).text();
            var variableName = "FTestMatrix"+i+""+j;
            bv.SetPluginStringParameter(variableName, text);
        }
    }

    //Setting statistic to use
    bv.SetPluginStringParameter("Statistic", dlg.optionsGroupBox.statisticToUseComboBox.currentText);

    //Setting refreshing time for log
    bv.SetPluginIntParameter("RefreshingTime", dlg.optionsGroupBox.refreshingTimeSpinBox.value);

    //Setting plugin command
    bv.SetPluginStringParameter("Command", "Execute");

    //GO!!!
    bv.ExecutePlugin();
}


scriptObj.onChangeStudy = function(){
    var currentStudy = studies.currentText;
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

        while(contrastMatrix.rowCount != 0){
            this.removeContrast();
        }
        while(designMatrix.columnCount != 0){
            this.removeColumn();
        }
        while(ftestMatrix.columnCount != 0){
            this.removeFTest();
        }
        while(treeMatrix.columnCount != 0){
            this.removeGroup();
        }

        if(currentStudy == "One-Sample T-Test"){
            //Setting permutation hypothesis
            dlg.optionsGroupBox.iseCheckBox.setChecked(true);

            //Adding necessary rows/columns to tables
            this.addColumn();
            this.addContrast();
            this.addGroup();

            //Filling Design Matrix and Group Matrix
            for(i = 0; i < num_of_maps; i++){
                addEntryToTable(designMatrix, i, 0, "1");
                addEntryToTable(treeMatrix, i, 0, "1");
            }

            //Filling the contrast matrix
            addEntryToTable(contrastMatrix, 0, 0, "1");

            //Setting proper statistic
            dlg.optionsGroupBox.statisticToUseComboBox.setCurrentText("T");
        }
        else if(currentStudy == "Two-Sample Unpaired T-Test"){
            //Setting permutation hypothesis
            dlg.optionsGroupBox.eeCheckBox.setChecked(true);

            //Adding necessary rows/columns to tables
            this.addColumn();
            this.addColumn();
            this.addContrast();
            this.addGroup();

            //Filling the design matrix
            for(var i = 0; i < num_of_maps/2; i++){
                addEntryToTable(designMatrix, i, 0, "1");
                addEntryToTable(designMatrix, i, 1, "0");
            }
            for(var i = num_of_maps/2; i < num_of_maps; i++){
                addEntryToTable(designMatrix, i, 0, "0");
                addEntryToTable(designMatrix, i, 1, "1");
            }

            //Filling the group matrix
            for(var i = 0; i < num_of_maps; i++){
                addEntryToTable(treeMatrix, i, 0, "1");
            }

            //Filling the contrast matrix
            addEntryToTable(contrastMatrix, 0, 0, "1");
            addEntryToTable(contrastMatrix, 0, 1, "-1");

            //Setting proper statistic
            dlg.optionsGroupBox.statisticToUseComboBox.setCurrentText("T");

        }else if(currentStudy == "Two-Sample Paired T-Test"){
            //Getting number of subjects
            var num_subjects = num_of_maps/2;

            //Setting permutation hypothesis
            dlg.optionsGroupBox.eeCheckBox.setChecked(true);

            //Adding necessary rows/columns to tables
            this.addColumn();
            for(var i = 0; i < num_subjects; i++){
                this.addColumn();
            }
            this.addContrast();
            this.addGroup();
            this.addGroup();

            //Filling the design matrix
            //First column
            for(var i = 0; i < num_of_maps; i+=2){
                addEntryToTable(designMatrix, i,0, "1");
                addEntryToTable(designMatrix, i+1,0, "-1");
            }
            //Other columns
            for(var j = 1; j < num_subjects+1; j++){
                var nsubj = j - 1;
                for(var i = 0; i < num_of_maps; i++){
                    if(i/2 == nsubj || i/2 - 0.5 == nsubj){
                        addEntryToTable(designMatrix, i, j, "1");
                    }
                    else{
                        addEntryToTable(designMatrix, i, j, "0");
                    }
                }
            }

            //Filling the group matrix
            //First column
            for(var i = 0; i < num_of_maps; i++){
                addEntryToTable(treeMatrix, i,0, "-1");
            }
            //Second column
            var group = 1;
            for(var i = 0; i < num_of_maps; i+=2){
                var group_string = ""+group;
                addEntryToTable(treeMatrix, i,1, group_string);
                addEntryToTable(treeMatrix, i+1,1, group_string);
                group += 1;
            }

            //Filling the contrast matrix
            addEntryToTable(contrastMatrix, 0, 0, "1");
            for(var j = 1; j < num_subjects+1; j++){
                addEntryToTable(contrastMatrix, 0, j, "0");
            }

            //Setting proper statistic
            dlg.optionsGroupBox.statisticToUseComboBox.setCurrentText("T");

        }else if(currentStudy == "ANOVA: 1 factor 4 levels (Repeated measures)"){
            //Getting number of subjects
            var num_subjects = num_of_maps/4;

            //Setting permutation hypothesis
            dlg.optionsGroupBox.eeCheckBox.setChecked(true);

            //Adding necessary rows/columns to tables
            this.addColumn();
            this.addColumn();
            this.addColumn();
            for(var i = 0; i < num_subjects; i++){
                this.addColumn();
            }
            this.addContrast();
            this.addContrast();
            this.addContrast();
            this.addFTest();
            this.addGroup();
            this.addGroup();
            
            //Filling the design matrix
            //First num_subjects columns
            for(var j = 0; j < num_subjects; j++){
                for(var i = 1; i <= num_of_maps; i++){
                    if(i > 4*j && i <= 4*(j+1)){
                        addEntryToTable(designMatrix, i-1,j, "1");
                    }else{
                        addEntryToTable(designMatrix, i-1,j, "0");
                    }
                }
            }
            //Other columns
            for(var j = num_subjects; j < num_subjects+3; j++){
                var k = j - num_subjects;
                for(var i = 0; i < num_of_maps; i++){
                    if(i % 4 == k){
                        addEntryToTable(designMatrix, i,j, "1");
                    }else{
                        addEntryToTable(designMatrix, i,j, "0");
                    }
                }
            }

            //Filling the group matrix
            //First column
            for(var i = 0; i < num_of_maps; i++){
                addEntryToTable(treeMatrix, i,0, "-1");
            }
            //Second column
            var group = 1;
            for(var j = 0; j < num_subjects; j++){
                var group_string = ""+group;
                for(var i = 0; i < 4; i++){
                    addEntryToTable(treeMatrix, 4*j+i,1, group_string);
                }
                group += 1;
            }
            
            //Filling the contrast matrix
            //First num_subjects columns
            for(var i = 0; i < num_subjects; i++){
                for(var j = 0; j < 3; j++){
                    addEntryToTable(contrastMatrix, j, i, "0");
                }
            }
            //Other columns
            for(var i = num_subjects; i < num_subjects+3; i++){
                for(var j = 0; j < 3; j++){
                    if(i-num_subjects == j){
                        addEntryToTable(contrastMatrix, j, i, "1");
                    }else{
                        addEntryToTable(contrastMatrix, j, i, "0");
                    }
                }
            }

            //Filling the FTestMatrix
            for(var i = 0; i < 3; i++){
                addEntryToTable(ftestMatrix, i, 0, "1");
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
