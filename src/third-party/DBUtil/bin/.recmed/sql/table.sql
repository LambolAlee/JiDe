/* ================== create info_patient and its trigger =================== */
CREATE TABLE info_patient (
    id              INTEGER PRIMARY KEY ASC,                            -- 病人id
    patient_name    NCHAR(8) NOT NULL,                                  -- 病人姓名
    sex             BOOLEAN DEFAULT 1,                                  -- 病人性别
    flag            UNSIGNED TINYINT DEFAULT 0,                         -- 重名标志位
    birthday        DATE DEFAULT CURRENT_DATE,                          -- 出生日期
    ethnicity       UNSIGNED TINYINT DEFAULT 0,                         -- 民族
    native_place    NCHAR(8) DEFAULT '',                                -- 籍贯
    birth_place     NCHAR(8) DEFAULT '',                                -- 出生地
    career          NCHAR(8) DEFAULT '',                                -- 职业
    created_at      TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at      TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);


/* ================== create info_record and its trigger =================== */
CREATE TABLE info_record (
    id              INTEGER PRIMARY KEY ASC,        -- 病历id
    patient_id      INTEGER NOT NULL,               -- 相关病人id
    is_reexam       BOOLEAN DEFAULT 0,              -- 初诊还是复诊
    parent_record   INTEGER,                        -- 复诊关联的初诊病历id
    clinic_date     DATE DEFAULT CURRENT_DATE,      -- 就诊日期
    age             UNSIGNED TINYINT DEFAULT 0,     -- 就诊时年龄
    doctor_name     NCHAR(8) NOT NULL,              -- 医生姓名
    doctor_id       INTEGER NOT NULL,               -- 医生id
    place           NCHAR(20) DEFAULT 'hospital',    -- 就诊医院
    created_at      TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at      TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);

CREATE TRIGGER "init_parent"        -- 提供默认的父病历，默认父病历是自身，除非指定了parent_record的值
AFTER INSERT
ON "info_record"
FOR EACH ROW
BEGIN
	UPDATE info_record SET parent_record = id WHERE parent_record ISNULL;
END;


/* ================== create state_illness and its trigger =================== */
CREATE TABLE state_illness (
    id                  INTEGER PRIMARY KEY ASC,
    record_id           INTEGER NOT NULL,
    complaint           NVARCHAR(20) DEFAULT '',
    inducing_fator      NVARCHAR(100) DEFAULT '',
    main_ph             TEXT DEFAULT '',
    simul_ph            TEXT DEFAULT '',
    treatment_history   TEXT DEFAULT '',
    other_ph            TEXT DEFAULT '',
    present_ph          TEXT DEFAULT '',
    reason              NVARCHAR(20) DEFAULT '',
    tcm_ph              NVARCHAR(100) DEFAULT '',
    created_at      TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at      TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);


/* ================== create diagnosis and its trigger =================== */
CREATE TABLE diagnosis (
    id              INTEGER PRIMARY KEY ASC,
    record_id       INTEGER NOT NULL,
    tcm_diagnosis   TEXT DEFAULT '',
    wm_diagnosis    TEXT DEFAULT '',
    created_at      TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at      TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);


/* ================== create treatment and its trigger =================== */
CREATE TABLE treatment (
    id                      INTEGER PRIMARY KEY ASC,
    record_id               INTEGER NOT NULL,
    formular                TEXT DEFAULT '',
    formular_count          UNSIGNED TINYINT DEFAULT 0,
    advice                  NVARCHAR(40) DEFAULT '',
    usage                   NVARCHAR(20) DEFAULT '',
    other_tcm_treatment     TEXT DEFAULT '',
    nursing                 NVARCHAR(100) DEFAULT '',
    wm_treatment            TEXT DEFAULT '',
    created_at      TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at      TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);
