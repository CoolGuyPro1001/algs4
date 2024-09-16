#include "LinearRegression.h"

LinearRegression::LinearRegression(std::vector<double> x, std::vector<double> y)
{
    if (x.size() != y.size())
    {
        error("array lengths are not equal");
    }
    int n = x.size();

    // first pass
    double sum_x = 0.0, sum_y = 0.0, sum_x2 = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum_x  += x[i];
        sum_x2 += x[i] * x[i];
        sum_y  += y[i];
    }
    double x_bar = sum_x / n;
    double y_bar = sum_y / n;

    // second pass: compute summary statistics
    double xx_bar = 0.0, yy_bar = 0.0, xy_bar = 0.0;
    for (int i = 0; i < n; i++) {
        xx_bar += (x[i] - x_bar) * (x[i] - x_bar);
        yy_bar += (y[i] - y_bar) * (y[i] - y_bar);
        xy_bar += (x[i] - x_bar) * (y[i] - y_bar);
    }
    m_slope  = xy_bar / xx_bar;
    m_intercept = y_bar - m_slope * x_bar;

    // more statistical analysis
    double rss = 0.0;      // residual sum of squares
    double ssr = 0.0;      // regression sum of squares
    for (int i = 0; i < n; i++)
    {
        double fit = m_slope * x[i] + m_intercept;
        rss += (fit - y[i]) * (fit - y[i]);
        ssr += (fit - y_bar) * (fit - y_bar);
    }

    int degrees_of_freedom = n-2;
    m_r2    = ssr / yy_bar;
    double svar  = rss / degrees_of_freedom;
    m_svar1 = svar / xx_bar;
    m_svar0 = svar/n + x_bar * x_bar * m_svar1;
}

double LinearRegression::intercept() const
{
    return m_intercept;
}

double LinearRegression::slope() const
{
    return m_slope;
}

double LinearRegression::R2() const
{
    return m_r2;
}

double LinearRegression::intercept_stderr() const
{
    return std::sqrt(m_svar0);
}

double LinearRegression::slope_stderr() const
{
    return std::sqrt(m_svar1);
}

double LinearRegression::predict(double x) const
{
    return m_slope * x + m_intercept;
}

std::string LinearRegression::to_string() const
{
    return std::format("{:.2f} n + {:.2f}  (R^2 = {:.3f})", slope(), intercept(), R2());
}