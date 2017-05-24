## General Liner Model notation ##

Before exploring the permutation strategies appliable to GLM, it's important to give a proper notation.

At each spatial point (voxel, vertex or face) of an image representation of the brain, a *general linear model* can be formulated and expressed as:

<p style="text-align: center; font-size: large;">
$Y = M\phi + \epsilon$
</p>

where:

- $Y$ is the $N x 1$ vector of observed data.
- $M$ is the full rank $N x r$ design matrix that includes all effects of interest as well as modelled nuisance effects.
- $\phi$ is the $r x 1$ vector of $r$ regression coefficients.
- $\epsilon$ is the $N x 1$ vector of random errors.

Estimates for the regression coefficients can be computed as $\phi_{est.} = M^+Y$, where the superscript ($^+$) denotes the Moore-Penrose pseudo-inverse. Our interest is to test the null hypothesis that an arbitraty combination (contrast) of some or all of these parameters is equal to zero, that is


<p style="text-align: center; font-size: large;">
$H_0 : C'\phi = 0$
</p>

where $C$ is a $r x s$ full-rank matrix of $s$ contrasts, 1 $\leq s \leq r$.

## Permutations and exchangeability ##

To be continued...
