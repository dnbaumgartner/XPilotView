/*
 * This file is part of XPilotView.
 *
 * XPilotView is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XPilotView is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XPilotView.  If not, see <http://www.gnu.org/licenses/>
 */

/*
 * File:   PreferencesPanel.cpp
 * Author: dave
 *
 * Created on August 7, 2017, 10:03 PM
 */

#include "PreferencesPanel.hpp"

PreferencesPanel::PreferencesPanel()
{
    widget.setupUi(this);
    preferences = KeyValueStore::Instance();
    this->updateUI();
}

PreferencesPanel::~PreferencesPanel()
{
}

void PreferencesPanel::on_ttyPathLineEdit_editingFinished()
{
    QLineEdit* lineEdit = widget.ttyPathLineEdit;
    preferences->setValue("ttyPath", lineEdit->text().toStdString());
}

void PreferencesPanel::on_rollCurvatureLineEdit_editingFinished()
{
    QLineEdit* lineEdit = widget.rollCurvatureLineEdit;
    preferences->setValue("rollCurvature", lineEdit->text().toStdString());
}

void PreferencesPanel::on_pitchCurvatureLineEdit_editingFinished()
{
    QLineEdit* lineEdit = widget.pitchCurvatureLineEdit;
    preferences->setValue("pitchCurvature", lineEdit->text().toStdString());
}

void PreferencesPanel::on_yawCurvatureLineEdit_editingFinished()
{
    QLineEdit* lineEdit = widget.yawCurvatureLineEdit;
    preferences->setValue("yawCurvature", lineEdit->text().toStdString());
}

void PreferencesPanel::on_filterLagLineEdit_editingFinished()
{
    QLineEdit* lineEdit = widget.filterLagLineEdit;
    preferences->setValue("filterLag", lineEdit->text().toStdString());
}

void PreferencesPanel::on_savePushButton_clicked()
{
    preferences->save();
}

void PreferencesPanel::updateUI()
{
    QLineEdit* lineEdit = widget.ttyPathLineEdit;
    lineEdit->setText(QString::fromStdString(preferences->getValue("ttyPath")));
    lineEdit = widget.yawCurvatureLineEdit;
    lineEdit->setText(QString::fromStdString(preferences->getValue("yawCurvature")));
    lineEdit = widget.pitchCurvatureLineEdit;
    lineEdit->setText(QString::fromStdString(preferences->getValue("pitchCurvature")));
    lineEdit = widget.rollCurvatureLineEdit;
    lineEdit->setText(QString::fromStdString(preferences->getValue("rollCurvature")));
    lineEdit = widget.filterLagLineEdit;
    lineEdit->setText(QString::fromStdString(preferences->getValue("filterLag")));
}