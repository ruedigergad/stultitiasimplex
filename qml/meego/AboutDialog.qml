/*
 *  Copyright 2012 Ruediger Gad
 *
 *  This file is part of StultitiaSimplex.
 *
 *  StultitiaSimplex is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  StultitiaSimplex is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with StultitiaSimplex.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 1.1
import com.nokia.meego 1.0

Dialog {
    id: aboutDialog

    content:Item {
      anchors.fill: parent

      Text {id: homepage;
          text: "<a href=\"https://github.com/ruedigergad/stultitiasimplex\" style=\"text-decoration:none; color:#ff9900" >StultitiaSimplex - Version 2.0.0</a><br /><a href=\"https://github.com/ruedigergad/stultitiasimplex\"><img src=\"qrc:/svg/icon_text_card_white.png\" /></a>";
          textFormat: Text.RichText;
          onLinkActivated: { Qt.openUrlExternally(link); }
          font.pixelSize: 25; horizontalAlignment: Text.AlignHCenter;
          anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: description.top; anchors.bottomMargin: 8 }

      Text {id: description; text: "A Simple SoundBoard"; font.pixelSize: 25; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: author.top; anchors.bottomMargin: 12; color: "white"}

      Text {id: author;
          text: "Authors: <br />"
                 + "Ruediger Gad - <a href=\"mailto:r.c.g@gmx.de\" style=\"text-decoration:none; color:#ff9900\" >r.c.g@gmx.de</a><br />"
          textFormat: Text.RichText;
          onLinkActivated: { Qt.openUrlExternally(link); }
          font.pixelSize: 20; anchors.centerIn: parent; color: "lightgray"; horizontalAlignment: Text.AlignHCenter}

      Text {id: license;
          text: "StultitiaSimplex is free software: you can redistribute it and/or modify "
            + "it under the terms of the <a href=\"http://www.gnu.org/licenses\" style=\"text-decoration:none; color:#ff9900\" >GNU General Public License</a> as published by "
            + "the Free Software Foundation, either version 3 of the License, or "
            + "(at your option) any later version.";
          textFormat: Text.RichText;
          onLinkActivated: { Qt.openUrlExternally(link); }
          font.pixelSize: 18;
          anchors.horizontalCenter: parent.horizontalCenter;
          anchors.top: author.bottom;
          anchors.topMargin: 12;
          width: parent.width;
          color: "lightgray";
          horizontalAlignment: Text.AlignHCenter;
          wrapMode: Text.Wrap}
    }
}
