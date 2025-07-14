# Generalized Pell Equation Solutions Analysis

A comprehensive exploration of integer solutions to the generalized Pell equation

\{
x^2 - Dy^2 = N
\}

for non‑square \(D\in[2,100)\), \(N\in[-100,100]\).  
This repository contains:
- **Dataset**: Monte‑Carlo–generated CSV of \((D,N,x,y)\) plus `num_classes` (number of equivalence classes).
- **Notebooks**: Data processing, visualization, statistical summaries, outlier detection, clustering, and ML modeling in Google Colab.
- **Results**: Key insights and figures illustrating the rich behavior of Pell solutions and the challenges in predicting solution structure.

---

## 📑 Dataset

- **Rows**: 1000 trials of random \((D,N)\).
- **Columns**:
  - `D` – positive non‑square integer (2–99)
  - `N` – nonzero integer (−100 to +100)
  - `num_classes` – number of equivalence classes of integer solutions for that \((D,N)\)
  - `x, y` – one representative solution per class, extended by powers of the fundamental unit
- **Zero‑solution cases**: 824 trials produced no solutions (`num_classes = 0`, `x=y=0`).

---

## 🔍 Exploratory Analysis

1. **Distributions**  
   - `D` and `N` span their ranges nearly uniformly.  
   - `num_classes` is heavily skewed toward 2 (most solvable \((D,N)\) have exactly two classes).  
   - \(\log_{10}|x|\), \(\log_{10}|y|\) show a heavy right tail: a few solutions reach hundreds of digits, while most remain modest.

2. **Correlations**  
   - \(\log|x|\) vs. \(\log|y|\): almost perfectly correlated.  
   - Moderate correlation between `D` and solution size (larger \(D\) → larger minimal solutions).  
   - **Weak**/negligible linear correlation of \((D,N)\) with `num_classes`.

3. **Scatter & Heatmap**  
   - Scatterplot of \((D,N)\) colored by `num_classes` shows intermingled class counts—no simple clustering by \((D,N)\).  
   - Feature‐correlation heatmap confirms that only solution size features cluster strongly.

---

## 📊 Visualizations

> _All figures are in the `figures/` folder or embedded in the Colab notebook._

- **Histogram of** `D`, `N`, `num_classes`
- **Density plots** of \(\log_{10}|x|\) and \(\log_{10}|y|\)
- **Scatter** \((D,N)\) → `num_classes`
- **Heatmap** of pairwise correlations
- **Boxplots** highlighting the extreme spread of solution sizes

---

## ⚠️ Outlier & Anomaly Detection

- **High class counts** (5–6) are rare. Example \((D,N)\) with `num_classes = 6`:  
  - \((5,-76)\), \((53,-52)\), \((58,63)\), \((61,52)\), \((85,-76)\)  
- **Astronomical solutions**:  
  - E.g. \((D,N) = (61,52)\) yields minimal \(x,y\) with \(\sim\!200\) digits.  
- These extremes reflect deep number‑theoretic phenomena, not data errors.

---

## 🧮 Regression & Clustering

- **Linear / Polynomial Regression** on \((D,N)\) → `num_classes`:  
  - \(R^2\approx0.01\) (linear), \(R^2\approx0.07\) (quadratic).  
- **K‑means & DBSCAN** on \((D,N)\) or \((\log|x|,\log|y|)\):  
  - Separates trivial “no‑solution” vs. “solvable” groups, or by solution magnitude, but not by class count.

---

## 🤖 Predictive Modeling

- **Goal**: predict `num_classes` from \((D,N,x,y)\).
- **Features**:  
  - \(D\), \(N\), \(\log_{10}|x|\), \(\log_{10}|y|\)  
- **Models**:
  - Decision Tree → ~99.7% train/test accuracy  
  - Random Forest → ~99.9% train/test accuracy  
- **Caveat**: Very high scores reflect memorization of repeated \((D,N)\) labels. Real‑world generalization to new \((D,N)\) is far harder.

---

## 💡 Key Insights

- **Unpredictable solution sizes**: Even for adjacent \(D\), minimal solutions can be “tiny” or “huge,” matching classical theory.  
- **Class count irregularity**: Most solvable equations yield exactly two equivalence classes; higher counts are algebraically special.  
- **Weak direct predictors**: Neither \(D\) nor \(N\) alone, nor low‑degree combinations, reliably predict class count.  
- **Memorization risk**: Supervised models excel on known \((D,N)\) but don’t capture underlying number‑theoretic structure.

---


---

## 📖 References

1. Robertson, J. P. (2004). _Solving the generalized Pell equation \(x^2 - D y^2 = N\)_.  
2. Matthews, K. R. (2000). _Diophantine equations \(x^2 - D y^2 = N\)_ (LMM algorithm).  
3. Niven, Zuckerman & Montgomery (1991). _An Introduction to the Theory of Numbers_.  
4. Mollin, R. E. (1998). _Fundamental Number Theory with Applications_.

---

## 🚀 Getting Started

1. Clone this repo  
2. Open the Colab notebooks in `/notebooks/`  
3. Install required packages:
   ```bash
   pip install pandas numpy matplotlib seaborn scikit-learn
4. Run cells in order.

