var sheet_id = "1lTd18Ua0Kd1E_O2AZYkL6EkH6GrWa5N13gQ-C3ds2Mk";
var sheet_name = "esp32_data";
function doGet(e){
var ss = SpreadsheetApp.openById(sheet_id);
var sheet = ss.getSheetByName(sheet_name);
var timeH = Number(e.parameter.timeH);
var timeM = Number(e.parameter.timeM);
var clickedM = Number(e.parameter.clickedM);
var clickedH = Number(e.parameter.clickedH);
sheet.appendRow([timeH,timeM,clickedM,clickedH]);
}