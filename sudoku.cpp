#include "sudoku.h"
#include "ui_sudoku.h"
#include <iostream>

Sudoku::Sudoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sudoku)
{
    ui->setupUi(this);
    QWidget::connect(this->ui->solve, SIGNAL(clicked(bool)), this, SLOT(solve()));
    QWidget::connect(this->ui->clear, SIGNAL(clicked(bool)), this, SLOT(clear()));
}

Sudoku::~Sudoku()
{
    delete ui;
}

space Sudoku::get_value(QLineEdit *q)
{
    auto sp = space{};
    sp.view = q;
    bool ok;
    int value = q->text().toInt(&ok, 10);
    if (!ok) {
        q->setText("");
        sp.number = 0;
        sp.locked = false;
        q->setStyleSheet("QLineEdit{color: black;};");
        return sp;
    }
    sp.number = value;
    sp.locked = true;
    q->setStyleSheet("QLineEdit{color: red;};");
    return sp;
}

std::vector<space> Sudoku::get_values()
{
    std::vector<space> values;
    {
        // row 0
        values.push_back(this->get_value(this->ui->tltl));
        values.push_back(this->get_value(this->ui->tltm));
        values.push_back(this->get_value(this->ui->tltr));

        values.push_back(this->get_value(this->ui->tmtl));
        values.push_back(this->get_value(this->ui->tmtm));
        values.push_back(this->get_value(this->ui->tmtr));

        values.push_back(this->get_value(this->ui->trtl));
        values.push_back(this->get_value(this->ui->trtm));
        values.push_back(this->get_value(this->ui->trtr));

        // row 1
        values.push_back(this->get_value(this->ui->tlml));
        values.push_back(this->get_value(this->ui->tlmm));
        values.push_back(this->get_value(this->ui->tlmr));

        values.push_back(this->get_value(this->ui->tmml));
        values.push_back(this->get_value(this->ui->tmmm));
        values.push_back(this->get_value(this->ui->tmmr));

        values.push_back(this->get_value(this->ui->trml));
        values.push_back(this->get_value(this->ui->trmm));
        values.push_back(this->get_value(this->ui->trmr));

        // row 2
        values.push_back(this->get_value(this->ui->tlbl));
        values.push_back(this->get_value(this->ui->tlbm));
        values.push_back(this->get_value(this->ui->tlbr));

        values.push_back(this->get_value(this->ui->tmbl));
        values.push_back(this->get_value(this->ui->tmbm));
        values.push_back(this->get_value(this->ui->tmbr));

        values.push_back(this->get_value(this->ui->trbl));
        values.push_back(this->get_value(this->ui->trbm));
        values.push_back(this->get_value(this->ui->trbr));
    }
    {
        // row 3
        values.push_back(this->get_value(this->ui->mltl));
        values.push_back(this->get_value(this->ui->mltm));
        values.push_back(this->get_value(this->ui->mltr));

        values.push_back(this->get_value(this->ui->mmtl));
        values.push_back(this->get_value(this->ui->mmtm));
        values.push_back(this->get_value(this->ui->mmtr));

        values.push_back(this->get_value(this->ui->mrtl));
        values.push_back(this->get_value(this->ui->mrtm));
        values.push_back(this->get_value(this->ui->mrtr));

        // row 4
        values.push_back(this->get_value(this->ui->mlml));
        values.push_back(this->get_value(this->ui->mlmm));
        values.push_back(this->get_value(this->ui->mlmr));

        values.push_back(this->get_value(this->ui->mmml));
        values.push_back(this->get_value(this->ui->mmmm));
        values.push_back(this->get_value(this->ui->mmmr));

        values.push_back(this->get_value(this->ui->mrml));
        values.push_back(this->get_value(this->ui->mrmm));
        values.push_back(this->get_value(this->ui->mrmr));

        // row 5
        values.push_back(this->get_value(this->ui->mlbl));
        values.push_back(this->get_value(this->ui->mlbm));
        values.push_back(this->get_value(this->ui->mlbr));

        values.push_back(this->get_value(this->ui->mmbl));
        values.push_back(this->get_value(this->ui->mmbm));
        values.push_back(this->get_value(this->ui->mmbr));

        values.push_back(this->get_value(this->ui->mrbl));
        values.push_back(this->get_value(this->ui->mrbm));
        values.push_back(this->get_value(this->ui->mrbr));
    }
    {
        // row 6
        values.push_back(this->get_value(this->ui->bltl));
        values.push_back(this->get_value(this->ui->bltm));
        values.push_back(this->get_value(this->ui->bltr));

        values.push_back(this->get_value(this->ui->bmtl));
        values.push_back(this->get_value(this->ui->bmtm));
        values.push_back(this->get_value(this->ui->bmtr));

        values.push_back(this->get_value(this->ui->brtl));
        values.push_back(this->get_value(this->ui->brtm));
        values.push_back(this->get_value(this->ui->brtr));

        // row 7
        values.push_back(this->get_value(this->ui->blml));
        values.push_back(this->get_value(this->ui->blmm));
        values.push_back(this->get_value(this->ui->blmr));

        values.push_back(this->get_value(this->ui->bmml));
        values.push_back(this->get_value(this->ui->bmmm));
        values.push_back(this->get_value(this->ui->bmmr));

        values.push_back(this->get_value(this->ui->brml));
        values.push_back(this->get_value(this->ui->brmm));
        values.push_back(this->get_value(this->ui->brmr));

        // row 8
        values.push_back(this->get_value(this->ui->blbl));
        values.push_back(this->get_value(this->ui->blbm));
        values.push_back(this->get_value(this->ui->blbr));

        values.push_back(this->get_value(this->ui->bmbl));
        values.push_back(this->get_value(this->ui->bmbm));
        values.push_back(this->get_value(this->ui->bmbr));

        values.push_back(this->get_value(this->ui->brbl));
        values.push_back(this->get_value(this->ui->brbm));
        values.push_back(this->get_value(this->ui->brbr));
    }
    return values;
}

bool Sudoku::solve_space(std::vector<space> &spaces, int i)
{
    if (i >= spaces.size()) {
        return true;
    }
    if (spaces[i].locked) {
        return solve_space(spaces, i+1);
    }
    for (int j = 1; j < 10; ++j) {

        spaces[i].number = j;
        spaces[i].view->setText(QString(std::to_string(j).c_str()));
        this->repaint();

        if (check_space(spaces, i)) {
            if (solve_space(spaces, i+1)) {
                return true;
            }
        }
    }

    spaces[i].number = 0;
    spaces[i].view->setText(QString(""));
    return false;
}

bool Sudoku::check_space(const std::vector<space> &spaces, int i)
{
    const int size = 9;
    int row = i/size;
    int col = i%size;

    // check row
    for (int j = 0; j < 9; ++j) {
        int space = row * size + j;
        if (i == space) {
            continue;
        }
        if (spaces[i].number == spaces[space].number) {
            return false;
        }
    }
    // check column
    for (int j = 0; j < 9; ++j) {
        int space = (j * size) + col;
        if (i == space) {
            continue;
        }
        if (spaces[i].number == spaces[space].number) {
            return false;
        }
    }

    // check cubicle
    int cx = col / 3;
    int cy = row / 3;
    int cubeSize = size / 3;
    for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < 3; ++k) {
            int space = (((cy*cubeSize)+k) * size) + ((cx*cubeSize) + j);
            if (i == space) {
                continue;
            }
            if (spaces[i].number == spaces[space].number) {
                return false;
            }
        }
    }


    return true;
}

void Sudoku::solve()
{
    auto values = this->get_values();
    this->solve_space(values, 0);
}

void Sudoku::clear()
{
    auto values = this->get_values();
    for (auto &i : values) {
        i.view->setText("");
    }
}
