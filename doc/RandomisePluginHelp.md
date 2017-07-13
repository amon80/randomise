%Randomise Plugin Help
## Overview ##
This plugin performs permutation tests and inference on multi-subject task related fMRI experiments. It requires a mult-study GLM analysis as input. For further details about permutation testing and its use on with the General Linear Model, refer to the following pages:

- [Permutation testing](PermutationTesting.html)
- [Permutation testing applied to GLM](PermutationTestingGlm.html)
- [Threshold Free Cluster Enhancement](Tfce.html)

For a feature comparison with the FSL Randomise, see [here](Comparison.html).

## Before running the plugin ##
The plugin needs the beta maps of the contrast of interest for each subject. Depending on the type of study, e.g. a paired t-test, there can also be more than one map for each subject. The beta maps can be easily generated using the "Overlay General Linear Model dialog", as shown below and in the User's Guide in topic "Creating Multi-Subject Contrast Maps from Multi-Subject GLMs" in the "Miscellaneous Tools" chapter.

### Example: creating maps for one sample t-test ###
First of all, we have to load the .vmr file related to the study (e.g. MNI / Talairach or average of normalized brains of participants). Then, we can load our .glm file from the Analysis -> Overlay General Linear Model menu item and select the contrast of interest. In the example, we want to study the group activation of the condition A1. After the contrast has been set, we move to the options menu to create the beta maps.
![](images/gui/loadglm1.png)

In the dialog, be sure to select "Create beta/contrast maps" and "Create separate maps for each subject", then click "Create maps".

![](images/gui/createbetamaps1.png)

After the beta maps have been created, you can view them in the &quot;Volume Maps&quot; dialog that can be invoked with the &quot;Analysis -&gt; Overlay Volume Maps&quot; menu item.

![](images/gui/A1betamaps.png)

## GUI description ##
After the creation of the beta maps, the plugin GUI can be launched from the "Plugins" menu. Note that the creation of the beta maps is essential, otherwise the GUI won't load at all; the "Log" pane of BrainVoyager will print a respective message.

![](images/gui/gui.png)

As you can see from the image, the GUI is divided into two main parts: **Design** and **Options**. A brief description of each component is provided below.

### Type of study ###
This combobox lets the user select the type of analysis she wants to perform. The default selection is "Custom", which means that the user must specify herself the design matrix, the contrast and the exchangeability tree using the buttons above each matrix and then fill the entries manually. If one of the other predefined studies is selected, then all the matrices and the options will be filled automatically. In this case, the buttons and the options will also be disabled.

### Design Matrix ###
The design matrix features one row for each beta map and one column for each regressor. Since the number of maps remains the same through the execution of the plugin, the user doesn't need to specify the number of rows as it is set automatically. As a result of this, the buttons above the matrix add and remove columns/regressors from it.

### Contrast Matrix ###
The contrast matrix features one column for each regressor specified in the design matrix and one row for each contrast specified by the user. In this case, since the number of regressors is set up in the design matrix, the buttons above the matrix add or remove rows/contrasts from it.

### F-Test matrix ###
The F-Test matrix is used in those designs in which F-Tests are involved. It features one row for each contrast and one column for each F-test. The buttons above the matrix add or remove columns/f-tests. The entry at row i, column j of this matrix specifies if the contrast i must be taken into account when composing f-test j.

### Exchangeability options and TFCE ###
This part of the options tab is pretty much self explanatory. For any doubts about exchangeability hypothesis and TFCE, refer to the pages linked above.

### Number of permutation requested ###
The number of permutation can be speficied by the user by modifying the value in the respective spin box. However, it should be noted that the number specified by the user aren't always the actual permutations performed by the plugin, but it can be thought as an upper bound. 

During the execution of the plugin, each contrast is treated separately. For one specific contrast, the maximum number of permutations depends on the design matrix, on the exchangeability tree and the hypothesis about the errors. After the maximum number of permutations is computed, it is compared with the number supplied by the user. If the number supplied by the user is inferior, than only that number of permutations will be performed. 

If this number is set to -1, exhaustive permutation analysis will be run for each contrast.

### Output and logging options ###
The results for each contrast/F Test are stored in separate folders. For each folder, these are the possible outputs:

1. A map of the statistic of your choice computed for that contrast.
2. A map of 1-p uncorrected p-values.
3. A map of 1-p FWER corrected p-values.
4. The permutation distribution of maximas used to compute the critical threshold for FWER correction.
5. A file with all the permutations executed.

It's important to note that the the last two outputs are connected. Each line of the distribution file is the maximal statistic score obtained on the permutation specified by the same line of the permutation file.

By selecting the "Use separate VMPs" option, in each folder there will be more than one VMP, each corrisponding to one output. Otherwise, the results will be stored as submaps of just 1 VMP.

## Tips & Tricks ##

### Perform a 2 sample paired t-test ###
Even if the 2 sample paired t-test is not listed among the classical studies, it is straightforward to perform it. The idea is very simple: Using the previous example, let's say we want to compare condition A1 vs condition B1. It is sufficient to generate, for each subject, a single map in which the conditions are compared within subject, as showed in the example below.

![](images/gui/twosamplegen.png)
![](images/gui/twosamplegenresult.png)

Using these generated maps, it is sufficient to perform a *One sample T Test* in the plugin to perform a *Two sample paired T Test*.

### I want to compute only the raw statistic. How do I do? ###
Since the number of permutations includes the original permutation, it is sufficient to set the number of desired permutations to 1, and choose only "Raw statistic" as output.

### Which type of standard analysis should I run? ###
The choice of analysis to perform depends on what you are searching for in your study:

- If you're looking for group effects, perform *One sample t test*.
- If you want to compare two conditions, perform a *Two sample paired t test* using the strategy previously explained.
- If your study involves patients and controls, and error variance can be assumed to be the same across all subjects, perform *Two sample unpaired t test*.
- If your study involves patients and controls, and error variance *cannot* be assumed to be the same across all subjects (i.e. patients with ASD, experiment involving twins etc.), perform *Two sample unpaired t test (unpaired group variance)*.
- If you want to confront a pair of different conditions over the same subjects, perform *Two sample paired t test*. 

The other predefined study available is ANOVA: 1 factor-4 level (Repeated measures), which is pretty much self explainatory.

### Modify a standard analysis ###
There are several reasons to modify one of the standard analysis listed in the plugin:

1. You may want to add additional covariates (e.g. age, sex, handedness) to the study.
2. The study doesn't suit your needs. For example, the two sample unpaired t test assumes that first half of your maps belong to the first sample, and the second half to the second sample, but that's not always the case.
3. You may want to build a custom study starting from one standard analysis.

The plugin gives you the opportunity to modify arbitrarily one of the standard analyses. To do so, first select a study different from "Custom". After the tables and the options are filled automatically, reselect "Custom". You'll notice that the setup remains the same, but now all the control buttons are enabled.

Now you can add regressors, layers to the exchangeability tree, ftests and contrasts. You can also change the hypothesis and the statistics used by the test.

### Choice of the statistic for custom analysis ###
The plugin offers three statistics:

- T statistic.
- F statistic.
- G statistic.

You won't probably know the last one, since it's not a real statistic but a generalization of known statistics (including F and T as well):

|                                                               |        rank(C) = 1       |  rank(C) > 1  |
|---------------------------------------------------------------|:------------------------:|:-------------:|
|       Homoscedastic errors, unrestriced exchangeability       |        Square of T       |    F-ratio    |
| Homoscedastic errors within group, restricted exchangeability | Square of  Aspin-Welch v | Welch's $v^2$ |

So, when setting up a custom analysis, the G statistic is probably your safest choice. However, it should be noted that since G statistic has a very complex equation involving lots of matrix products and so its computation degrades overall performance. It should thus only be used when strictly necessary.

## Computing & Visualizing results ##

After you've set up your study, click on the OK button on the bottom right of the GUI to start the computation. You will be prompted to a save dialog, in which you can specify the path where you want the results to be saved.

![](images/gui/save.png)

If the location chosen has write permission, then a folder with the specified name will be created, and the actual test will start. This will take a while, depending on the number of contrasts specified, the use of TFCE and the choice of the statistic. You can monitor the progress in the "Log" pane of BrainVoyager, which is updated after every time interval specified in the GUI.

![](images/gui/log.png)

Once the plugin has finished, you can view the results in the folder you specified, by loading the appropriate VMP.

![](images/gui/load.png)

![](images/gui/results.png)

## Reference ##
Algorithm: Anderson M. Winkler, Gerard R. Ridgway, Matthew A. Webster, Stephen M. Smith, Thomas E. Nichols.

Implementation: Marco Mecchia
