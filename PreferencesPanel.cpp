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

void PreferencesPanel::on_rollScaleLineEdit_editingFinished()
{
    QLineEdit* lineEdit = widget.rollScaleLineEdit;
    preferences->setValue("rollCurvature", lineEdit->text().toStdString());
}

void PreferencesPanel::on_pitchScaleLineEdit_editingFinished()
{
    QLineEdit* lineEdit = widget.pitchScaleLineEdit;
    preferences->setValue("pitchCurvature", lineEdit->text().toStdString());
}

void PreferencesPanel::on_headingScaleLineEdit_editingFinished()
{
    QLineEdit* lineEdit = widget.headingScaleLineEdit;
    preferences->setValue("headingCurvature", lineEdit->text().toStdString());
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
    lineEdit = widget.headingScaleLineEdit;
    lineEdit->setText(QString::fromStdString(preferences->getValue("headingCurvature")));
    lineEdit = widget.pitchScaleLineEdit;
    lineEdit->setText(QString::fromStdString(preferences->getValue("pitchCurvature")));
    lineEdit = widget.rollScaleLineEdit;
    lineEdit->setText(QString::fromStdString(preferences->getValue("rollCurvature")));
    lineEdit = widget.filterLagLineEdit;
    lineEdit->setText(QString::fromStdString(preferences->getValue("filterLag")));
}