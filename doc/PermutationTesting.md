% Permutation tests

*Permutatation tests* are a class of widely applicable non-parametric methods. They uses random shuffles of the data to get the correct distribution of a test statistic under a null hypothesis. They provide valid tests (that is, tests with advertised type I error), although they are more computationally intensive than standard parametric tests. They are most useful when we have insufficient information about the distribution of the data, are uncomfortable making assumptions about the distribution, or if the distribution of the test statistic is not easily computed.

Permutation tests were pioonered by Fisher and Pitman. Fisher demonstrated that the null hypothesis could be tested simply by observing, after permuting observations, how often the difference between means would exceed the difference found without permutation, and that for such test, no normality would be required. Pitman provided the first compolete mathematical framework for permutation methods.

## p-Values ##

For a certain test statistic $T$ and a particular observed value $T_0$ of this statistic after the experiment has been conducted, the p-valules is the probability of observing, by chance, a test statistic equal or larger than the one computed with the observed values:

<p style="text-align: center; font-size: large;">
$P(T \geq T_0|H_0)$. 
</p>

In parametric setting, under a number of assumptions, the p-values can be obtained by referring to the teoretical distribution of the chosens statistic (such as the $F$ distribution), either through a known formula, or using tabulated values. 

In non-parametric seggings, these assumptions are avoided. Instead, the data are randomly shuffled, many times, in a manner consistent with the null hypothesis. For each shuffling, a new realisation of the statistic, $T^*_j$, is computed, being $j$ a permutation index. An empirical distribution of $T^*$ is constructed, and from this null distribution a p-value is computed as 

<p style="text-align: center; font-size: large;">
1/$J\sum_jI(T^*_j \geq T_0)$
</p>

where $J$ is the number of shuffling performed, and $I(\cdot)$ is the indicator function. From this it can be seen that the non-parametric p-values are discrete, with each possible p-value being a multiple of 1$/J$. It is important to note that the permutation distribution should include the observed statistic without permutation, and thus the smallest possible p-value is 1/$J$, not zero.
