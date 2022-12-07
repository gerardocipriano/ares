import mysql from "mysql2/promise"

export function createConnection() {
    return mysql.createConnection({
      host: "casper-3.mysql.database.azure.com",
      user: "ares_svc_ws",
      password: "Areswebservice1",
      database: "Ares"
    })
  }