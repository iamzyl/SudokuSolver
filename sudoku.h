#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>
#include <QLineEdit>

namespace Ui {
class Sudoku;
}

struct space {
    int number;
    bool locked;
    QLineEdit *view;
};

class Sudoku : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sudoku(QWidget *parent = 0);
    ~Sudoku();

private:
    space get_value(QLineEdit *q);
    std::vector<space> get_values();
    bool solve_space(std::vector<space> &spaces, int i);
    bool check_space(const std::vector<space> &spaces, int i);
    Ui::Sudoku *ui;

public slots:
    void solve();
    void clear();
};

#endif // SUDOKU_H
