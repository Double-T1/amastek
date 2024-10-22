# AMASTek 森淨題目

共三題<br>
第一題回覆在 q1.cpp<br>
第二題 ER diagram 截圖在 q2.png，另外[連結](https://dbdiagram.io/d/6717501397a66db9a3d16437)提供可操作 ER diagram

簡單描述：
系統主要圍繞三個核心：員工、產品、訂單

1. 員工：人員管理和生產報工各有一個表格，並依序輸入其資訊
2. 產品：產品管理、庫存狀態、出庫、入庫都是連結在一起的內容
3. 定單：與產品為多對多的關係，另衍生出貨單

功能對照：

- 設定員工帳號資訊： employee table
- 設定產品資訊(編號和名稱)： product table
- 新增訂單，輸入資料: 出貨日期、產品清單(包含產品編號和數量)： order table/ order_product table
- 生產報工： production report table
- 產出回報： output_report table
- 訂單出貨： shipment table
- 入庫： stock_in table
- 出庫： stock_out table
- 庫存狀態： inventory table
- 每日產出： sum from output_report table
- 訂單狀態： filter from order table
  <br>
  第三題回覆在 q3.sql<br>
