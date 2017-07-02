% Permutation tests

*Permutatation tests* are a class of widely applicable non-parametric methods. They uses random shuffles of the data to get the correct distribution of a test statistic under a null hypothesis. They provide valid tests (that is, tests with advertised type I error), although they are more computationally intensive than standard parametric tests. They are most useful when we have insufficient information about the distribution of the data, are uncomfortable making assumptions about the distribution, or if the distribution of the test statistic is not easily computed.

Permutation tests were pioonered by Fisher and Pitman. Fisher demonstrated that the null hypothesis could be tested simply by observing, after permuting observations, how often the difference between means would exceed the difference found without permutation, and that for such test, no normality would be required. Pitman provided the first compolete mathematical framework for permutation methods.

## p-Values ##

For a certain test statistic $T$ and a particular observed value $T_0$ of this statistic after the experiment has been conducted, the *p-value* is the probability of observing, by chance, a test statistic equal or larger than the one computed with the observed values:

<p style="text-align: center; font-size: large;">
$P(T \geq T_0|H_0)$. 
</p>

In parametric setting, under a number of assumptions, the p-values can be obtained by referring to the theoretical distribution of the chosen statistic (such as the $F$ distribution), either through a known formula, or using tabulated values. 

In non-parametric settings, these assumptions are avoided. Instead, the data are randomly shuffled, many times, in a manner consistent with the null hypothesis. For each shuffling, a new realisation of the statistic, $T^*_j$, is computed, being $j$ a permutation index. An empirical distribution of $T^*$ is constructed, and from this null distribution a p-value is computed as 

<p style="text-align: center; font-size: large;">
1/$J\sum_jI(T^*_j \geq T_0)$
</p>

where $J$ is the number of shuffling performed, and $I(\cdot)$ is the indicator function. From this it can be seen that the non-parametric p-values are discrete, with each possible p-value being a multiple of 1$/J$. It is important to note that the permutation distribution should include the observed statistic without permutation, and thus the smallest possible p-value is 1/$J$, not zero.

## The multiple comparison problem ##

For each voxel we can produce a P-value, $p^k$, for the null hypothesis $H_0^k$, where the superscript $k$ indexes the voxels. If we have an a priori anatomical hypothesis concerning the experimentally induced effect at a single voxel, then we can simply test at that voxel using an appropriate $\alpha$ level test. If we don't have such precise anatomical hypotheses, evidence for an experimental effect must be assessed at each and every voxel. We must take account of the multiplicity of testing. Clearly 5% of voxels are expected to have P-values less than $\alpha = 0.05$. This is the essence of the **multiple comparisons problem**. In the language of multiple comparisons, these P-values are *uncorrected* P-values. Type I errors must be controlled overall, such that the probability of falsely declaring any region as significant is less than the nominal test level $\alpha$. Formally, we require a test procedure maintaining strong control over *image-wise* (*family-wise*) Type I error, giving *adjusted* P-values, P-values *corrected* for multiple comparisons.

A nonparametric resampling based approach provides an intuitive and easily implemented solution. The key realization is that the reasoning presented above for permutation tests at a single voxel rely on relabeling entire *images*, so the arguments can be extended to image level inference by considering an appropriate *maximal statistic*. If, under the omnibus null hypothesis, the labels are exchangeable with respect to the voxel statistic under consideration, then the labels are exchageable with respect to any statistic summarinzing the voxel statistic, such as their maxima.

One common approach is the **single threshold test**. With such tests, the statistic image is thresholded at a given *critical threshold*, and voxels with statistic values exceeding this threshold have their null hypotheses rejected. Rejection of the *omnibus hypothesis* (that all the voxel hypotheses are true) occurs if any voxel value exceeds the threshold, a situation clearly determined by the value of the maximum value of the statistic image over the volume of interest. Thus, consideration of the maximum voxel statistic deals with the multiple comparisons problem. For a valid omnibus test, the critical threshold is such that the probability that it is exceeded by the maximal statistic is less than $\alpha$. Thus, we require the distribution of the maxima of the null statistic image. The permutation approach can yield the distribution of the maximal statistic in a straightforward manner: Rather than compute the permutation distribution of the statistic at a particular voxel, we compute the permutation distribution of the maximal voxel statistic over the volume of interest. We reject the omnibus hypothesis at level $\alpha$ if the maximal statistic for the actual labeling of the experiment is in the top 100$\alpha%$ of the permutation distribution for the maximal statistic. The critical value is $c+1$ largest member of the permutation distribution, where $c=\lfloor\alpha*N\rfloor$ rounded down. Furthermore, we can reject the null hypothesis at any voxel with a statistic value exceeding this threshold. The critical value for the maximal statistic is the critical threshold for a single threshold test over the same volume of interest. This test can be shown to have *strong* control over *experiment-wise* Type I error.
