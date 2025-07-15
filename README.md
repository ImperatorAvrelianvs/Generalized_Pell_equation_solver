# 📘 Generalized Pell Equation Solutions Analysis

A comprehensive exploration of integer solutions to the generalized Pell equation:

<p align="center"><code><strong>x² − Dy² = N</strong></code></p>

for non‑square integers `D` and arbitrary integers `N`.

---

## 📂 Repository Contents

- **Dataset**: Monte Carlo–generated CSV of `(D, N, x, y)` with `num_classes` (number of equivalence classes).
- **Notebooks**: Google Colab notebooks for data cleaning, visualization, statistical analysis, outlier detection, clustering, and ML modeling.
- **Results**: Key insights and rich figures that capture the behavior of solutions and highlight prediction challenges.

---

## 📑 Dataset Overview

- **Trials**: 1000 randomly generated `(D, N)` pairs.
- **Columns**:
  - `D`: Positive non-square integer (2–99)
  - `N`: Non-zero integer (−100 to +100)
  - `num_classes`: Number of equivalence classes of integer solutions for the pair `(D, N)`
  - `x`, `y`: One representative solution per class (extended using the fundamental unit)

- **Zero-solution cases**: 824 entries have no solution (`num_classes = 0`, `x = y = 0`).

---

## 🔍 Exploratory Data Analysis

### 1. Distributions

- `D` and `N` values are nearly uniform across their ranges.
- `num_classes` distribution is heavily skewed toward 2 — most solvable cases yield exactly two equivalence classes.
- The values of `log₁₀|x|` and `log₁₀|y|` exhibit a long right tail:
  - Most solutions are modest.
  - A few extend to hundreds of digits.

### 2. Correlations

- `log|x|` and `log|y|`: near-perfect correlation.
- Moderate correlation between `D` and the size of minimal solutions.
- Weak or negligible linear correlation of `(D, N)` with `num_classes`.

### 3. Scatter & Heatmaps

- Scatterplot of `(D, N)` colored by `num_classes` shows no clear clustering.
- Heatmap of pairwise feature correlations reveals strong grouping only among solution magnitude features.

---

## 📊 Visualizations

> _All figures are saved in the `/figures/` folder or embedded in the Colab notebooks._

- Histograms of `D`, `N`, and `num_classes`
- Density plots of `log₁₀|x|` and `log₁₀|y|`
- Scatterplots of `(D, N)` → `num_classes`
- Correlation heatmaps
- Boxplots illustrating solution size spread

---

## ⚠️ Outliers & Anomalies

- **Rare high class counts** (5 or 6 classes) are found in cases like:
  - `(5, -76)`, `(53, -52)`, `(58, 63)`, `(61, 52)`, `(85, -76)`
- **Extreme solution sizes**:
  - Example: `(D, N) = (61, 52)` produces minimal `(x, y)` with ~200 digits
- These are not data errors, but true mathematical outliers.

---

## 🧮 Regression & Clustering Models

- **Regression on `(D, N)` → `num_classes`**:
  - Linear: R² ≈ 0.01
  - Quadratic: R² ≈ 0.07

- **Clustering (K-means / DBSCAN)** on:
  - `(D, N)` — separates trivial (no-solution) from solvable, but not by class count.
  - `(log|x|, log|y|)` — more meaningful clustering by solution size.

---

## 🤖 Predictive Modeling

- **Goal**: Predict `num_classes` using `(D, N, x, y)`-related features.
- **Features used**: `D`, `N`, `log₁₀|x|`, `log₁₀|y|`
- **Models & Results**:
  - Decision Tree: ~99.7% accuracy
  - Random Forest: ~99.9% accuracy
- **Note**: These models memorize known `(D, N)` labels. Generalization to unseen inputs remains extremely difficult due to number-theoretic complexity.

---

## 💡 Key Insights

- **Minimal solution sizes are unpredictable** — adjacent `D` values may have drastically different-sized solutions.
- **Most solvable `(D, N)` yield exactly 2 classes**, confirming theoretical predictions.
- **`D` and `N` alone are weak predictors** of class count or solution size.
- **Machine learning models can overfit** without truly capturing mathematical structure.

---

## 📖 References

1. Robertson, J. P. (2004). *Solving the Generalized Pell Equation*.
2. Matthews, K. R. (2000). *Diophantine Equations and the LMM Algorithm*.
3. Niven, Zuckerman & Montgomery (1991). *An Introduction to the Theory of Numbers*.
4. Mollin, R. E. (1998). *Fundamental Number Theory with Applications*.

---

## 🚀 Getting Started

1. Clone this repository:
   ```bash
   git clone https://github.com/your-username/pell-equation-analysis.git
   cd pell-equation-analysis
