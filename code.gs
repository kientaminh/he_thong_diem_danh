```js
var timeZone = "Asia/Jakarta";
var dateTimeFormat = "dd/MM/yyyy HH:mm:ss";
var logSpreadSheetId = "1vSSHADU6Jqw6idb1LNycORWxwKmK0mGBkHwVXL69t2k";
var attendanceLogSheetName = "attendance log";
var mainTabName = "main tab";

function onOpen() {
  var ui = SpreadsheetApp.getUi();
  ui.createMenu('Anyboards Menu')
    .addItem('Initial Setup', 'initialSetup')
    .addToUi();
}
function initialSetup() {

  if (!getAttendanceLogSheet()) {
    var mainSheet = SpreadsheetApp.getActiveSheet().setName(mainTabName);
    var rowData = ['UID', 'Name', 'Access', 'Visits Count', 'Last Visit'];
    mainSheet.getRange(1, 1, 1, rowData.length).setValues([rowData]);
    mainSheet.setColumnWidths(1, rowData.length + 1, 150);

    rowData = ['Date Time', 'UID', 'Name', 'Result', 'Command'];
    var attendanceSheet = SpreadsheetApp.getActiveSpreadsheet().insertSheet(attendanceLogSheetName);
    attendanceSheet.getRange(1, 1, 1, rowData.length).setValues([rowData]);
    attendanceSheet.setColumnWidths(1, rowData.length + 1, 150);
  }

  else {

    var ui = SpreadsheetApp.getUi();
    ui.alert('The spreadsheet system has already been initialized');
  }
}
function addNewUIDsFromAttendanceLog(row) {
  var mainTab = getMainSheet();
  var attendanceSheet = getAttendanceLogSheet();
  var data = mainTab.getRange(2, 1, mainTab.getLastRow(), 1).getValues();
  var registeredUIDs = []
  data.forEach(x => registeredUIDs.push(x[0]));
  registeredUIDs = data.map(function (x) { return x[0]; });
  registeredUIDs = [...new Set(registeredUIDs)]; // distinct
  var data
  if (row) {
    data = attendanceSheet.getRange(row, 1, 1, 2).getValues();
  } else {
    return -1
  }
  var uid = data[0][1]
  var visit = []
  if (registeredUIDs.includes(uid)) return 1
  else {
    visit.date = data[0][0];
    visit.uid = uid;
    registeredUIDs.push(uid);
  }
  var startRow = mainTab.getLastRow() + 1;
  data = [];
  var row = [];
  row[0] = visit.uid;
  row[1] = 'Unk'
  if (row[1] != 'Unk') {
    row[2] = 'Ok';
  }
  row[3] = 0;
  row[4] = visit.date;
  data.push(row);
  if (data.length > 0)
    mainTab.getRange(startRow, 1, data.length, data[0].length).setValues(data);
}
function removeCard(uid) {
  var mainTab = getMainSheet();
  var data = mainTab.getRange(2, 1, mainTab.getLastRow(), 1).getValues();
  var registeredUIDs = []
  data.forEach(x => registeredUIDs.push(x[0]));
  registeredUIDs = data.map(function (x) { return x[0]; });
  registeredUIDs = [...new Set(registeredUIDs)];
  var data = mainTab.getRange(2, 1, mainTab.getLastRow(), 1).getValues()
  for (var i = 0; i < mainTab.getLastRow() - 1; i++) {
    if (data[i] == uid) {
      mainTab.deleteRow(i + 2);
      return 1;
    }
  }
  return 0;
}

function rollCall(uid) {
  var dateTime = Utilities.formatDate(new Date(), timeZone, dateTimeFormat);
  var mainSheet = getMainSheet();
  var data = mainSheet.getDataRange().getValues();
  for (var i = 0; i < data.length; i++) {
    if (data[i][0] == uid) {
      var numOfVisits = mainSheet.getRange(i + 1, 4).getValue();
      mainSheet.getRange(i + 1, 4).setValue(numOfVisits + 1);
      mainSheet.getRange(i + 1, 5).setValue(dateTime + ' ');
      return 1
    }
  }
  return 0
}
function doGet(e) {
  var name
  var access
  var dateTime = Utilities.formatDate(new Date(), timeZone, dateTimeFormat);
  Logger.log(JSON.stringify(e)); // view parameters
  var result = 'Ok'; // assume success
  if (e.parameter == 'undefined') {
    result = 'No Parameters';
  }
  else {
    var uid = '';
    var command = ''
    for (var param in e.parameter) {
      var value = stripQuotes(e.parameter[param]);
      switch (param) {
        case 'uid':
          uid = value;
          break;
        case 'command':
          command = value;
          break;
        default:
          result = "unsupported parameter";
          break;
      }
    }

    var mainSheet = getMainSheet();
    var data = mainSheet.getDataRange().getValues();
    if (data.length == 0) return;
    for (var i = 0; i < data.length; i++) {
      if (data[i][0] == uid) {
        name = data[i][1];
        access = data[i][2];
        break;
      }
    }

    var attendanceSheet = getAttendanceLogSheet();
    data = [dateTime, uid, name, access, command];
    attendanceSheet.getRange(attendanceSheet.getLastRow() + 1, 1, 1, data.length).setValues([data]);
    var row = attendanceSheet.getLastRow();
    if (command == 'Them') {
      var isAdded = addNewUIDsFromAttendanceLog(row)
      if (isAdded == 1) {
        return ContentService.createTextOutput('The da duoc them:1:' + name)
      }
      else {
        return ContentService.createTextOutput('Success:1:' + name)
      }
    }
    else if (command == 'Xoa') {
      var isAdded = removeCard(uid)
      if (isAdded == 0) {
        return ContentService.createTextOutput('The chua them:-1:' + name)
      }
      else {
        return ContentService.createTextOutput('Success:-1:' + name)
      }
    }
    else if (command == 'DiemDanh') {
      var isAdded = rollCall(uid)
      if (isAdded == 0) {
        return ContentService.createTextOutput('The chua them:0:' + name)
      }
      else return ContentService.createTextOutput('Success:0:' + name)
    }
    else {
    }
  }
}

function getAttendanceLogSheet() {
  return SpreadsheetApp.getActiveSpreadsheet().getSheetByName(attendanceLogSheetName);
}

function getMainSheet() {
  return SpreadsheetApp.getActiveSpreadsheet().getSheetByName(mainTabName);
}

/**
 * Remove leading and trailing single or double quotes
 */
function stripQuotes(value) {
  return value.replace(/^["']|['"]$/g, "");
}

```
