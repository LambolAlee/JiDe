/* ================== create info_patient 患者信息 =================== */
CREATE TABLE info_patient (
    id              INTEGER PRIMARY KEY ASC,        -- 病人id
    patient_name    NCHAR(8) NOT NULL,              -- 病人姓名
    sex             BOOLEAN DEFAULT 1,              -- 病人性别
    flag            UNSIGNED TINYINT DEFAULT 0,     -- 重名标志位
    birthday        DATE DEFAULT CURRENT_DATE,      -- 出生日期
    ethnicity       UNSIGNED TINYINT DEFAULT 0,     -- 民族
    native_place    NCHAR(8) DEFAULT '',            -- 籍贯
    birth_place     NCHAR(8) DEFAULT '',            -- 出生地
    career          NCHAR(8) DEFAULT '',            -- 职业
    created_at      TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at      TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);


/* ================== create info_record and its trigger 基本病历信息 =================== */
CREATE TABLE info_record (
    id              INTEGER PRIMARY KEY ASC,        -- 病历id
    patient_id      INTEGER NOT NULL,               -- 相关病人id
    parent_record   INTEGER,                        -- 复诊关联的初诊病历id
    clinic_date     DATE DEFAULT CURRENT_DATE,      -- 就诊日期
    age             UNSIGNED TINYINT DEFAULT 0,     -- 就诊时年龄
    doctor_name     NCHAR(8) DEFAULT '',            -- 医生姓名
    /* doctor_id       INTEGER NOT NULL,               -- 医生id */
    place           NCHAR(20) DEFAULT 'hospital',   -- 就诊医院
    desc_text       TEXT DEFAULT 'new record',      -- 对该病历的简要描述
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


/* ================== create present_illness_history 现病史 =================== */
CREATE TABLE present_illness_history (
    id                  INTEGER PRIMARY KEY ASC,        -- 自动编号
    record_id           INTEGER NOT NULL,               -- 病历编号
    complaint           NVARCHAR(20) DEFAULT '',        -- 主诉
    inducing_fator      NVARCHAR(100) DEFAULT '',       -- 诱发因素
    main_ph             TEXT DEFAULT '',                -- 主要症状
    simul_ph            TEXT DEFAULT '',                -- 伴随症状
    treatment_history   TEXT DEFAULT '',                -- 既往治疗
    other_ph            TEXT DEFAULT '',                -- 其他症状
    present_ph          TEXT DEFAULT '',                -- 刻下症
    reason              NVARCHAR(20) DEFAULT '',        -- 就诊原因
    tcm_ph              NVARCHAR(100) DEFAULT '',       -- 中医四诊
    created_at          TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at          TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);


/* ================== create chronic_disease_history 慢性病史 =================== */
CREATE TABLE chronic_disease_history (
    id                      INTEGER PRIMARY KEY ASC,    -- 自动编号
    record_id               INTEGER NOT NULL,           -- 病历编号
    hypertension            TEXT DEFAULT '',            -- 高血压病史
    glycuresis              TEXT DEFAULT '',            -- 糖尿病病史
    coronary                TEXT DEFAULT '',            -- 冠心病病史
    hyperlipidemia          TEXT DEFAULT '',            -- 高脂血症病史
    hyperuricemia           TEXT DEFAULT '',            -- 高尿酸血症病史
    cerebral_infarction     TEXT DEFAULT '',            -- 脑梗死病史
    other                   TEXT DEFAULT '',            -- 其他慢性病史
    created_at              TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at              TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);


/* ================== create infectious_related_history 传染病相关史 =================== */
CREATE TABLE infectious_related_history (
    id                          INTEGER PRIMARY KEY ASC,    -- 自动编号
    record_id                   INTEGER NOT NULL,           -- 病历编号
    hepatitis                   TEXT DEFAULT '',            -- 肝炎史
    tuberculosis                TEXT DEFAULT '',            -- 结核病史
    other                       TEXT DEFAULT '',            -- 其他传染病史
    prophylactic_inoculation    NVARCHAR(255) DEFAULT '',   -- 预防接种史
    created_at                  TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at                  TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);


/* ================== create female_only 妇女专用 =================== */
CREATE TABLE female_only (
    id                      INTEGER PRIMARY KEY ASC,        -- 自动编号
    record_id               INTEGER NOT NULL,               -- 病历编号
    menarche                UNSIGNED TINYINT DEFAULT 0,     -- 初潮年龄
    menopause               BOOLEAN DEFAULT 1,              -- 是否绝经
    menopause_age           UNSIGNED TINYINT DEFAULT 0,     -- 绝经年龄
    last_menstruation       DATE DEFAULT CURRENT_DATE,      -- 末次月经
    menstrual_span          TEXT DEFAULT '',                -- 带经时间
    menstrual_cycle         UNSIGNED TINYINT DEFAULT 28,    -- 月经周期
    menstruation_ph         TEXT DEFAULT '',                -- 月经情况
    gestation               CHAR(5) DEFAULT '',             -- 孕产史
    created_at              TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at              TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);


/* ================== create personal_history 个人史 =================== */
CREATE TABLE personal_history (
    id                        INTEGER PRIMARY KEY ASC,      -- 自动编号
    record_id                 INTEGER NOT NULL,             -- 病历编号
    smoking                   NVARCHAR(32) DEFAULT '',      -- 吸烟史
    alcohol_intake            NVARCHAR(32) DEFAULT '',      -- 饮酒史
    drug_addiction            NVARCHAR(64) DEFAULT '',      -- 药物嗜好
    food_hobby                NVARCHAR(100) DEFAULT '',     -- 饮食习惯
    work_environ              NVARCHAR(100) DEFAULT '',     -- 工作条件
    exposure                  NVARCHAR(100) DEFAULT '',     -- 工业毒物、粉尘或放射性物质接触史
    metallurgy                NVARCHAR(100) DEFAULT '',     -- 冶游史
    marital_status            UNSIGNED TINYINT DEFAULT 0,   -- 婚姻状况
    marital_age               NVARCHAR(20) DEFAULT '',      -- 结婚年龄
    spouse_health             TEXT DEFAULT '',              -- 配偶健康状况
    children_count            UNSIGNED TINYINT DEFAULT 0,   -- 子女数
    children_health           TEXT DEFAULT '',              -- 子女健康状况
    family_history            TEXT DEFAULT '',              -- 家族史
    created_at                TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at                TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);


/* ================== create other_history 其他病史 =================== */
CREATE TABLE other_history (
    id                        INTEGER PRIMARY KEY ASC,      -- 自动编号
    record_id                 INTEGER NOT NULL,             -- 病历编号
    surgery                   TEXT DEFAULT '',              -- 手术史
    trauma                    TEXT DEFAULT '',              -- 外伤史
    blood_transfusion         TEXT DEFAULT '',              -- 输血史
    drug_allergy              TEXT DEFAULT '',              -- 药物过敏史
    food_allergy              TEXT DEFAULT '',              -- 食物过敏史
    created_at                TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at                TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);


/* ================== create hospital_exam 检查记录 =================== */
CREATE TABLE hospital_exam (
    id                        INTEGER PRIMARY KEY ASC,      -- 自动编号
    record_id                 INTEGER NOT NULL,             -- 病历编号
    laboratory_exam           TEXT DEFAULT '',              -- 实验室检查
    imaging_exam              TEXT DEFAULT '',              -- 影像检查
    instrument_exam           TEXT DEFAULT '',              -- 器械检查
    physical_exam             TEXT DEFAULT '',              -- 体格检查
    created_at                TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at                TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);


/* ================== create diagnosis 诊断 =================== */
CREATE TABLE diagnosis (
    id                        INTEGER PRIMARY KEY ASC,      -- 自动编号
    record_id                 INTEGER NOT NULL,             -- 病历编号
    tcm_diagnosis             TEXT DEFAULT '',              -- 中医病证
    tcm_syndrome              TEXT DEFAULT '',              -- 辨证类型
    wm_diagnosis              TEXT DEFAULT '',              -- 西医诊断
    created_at                TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at                TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);


/* ================== create treatment 治疗 =================== */
CREATE TABLE treatment (
    id                        INTEGER PRIMARY KEY ASC,      -- 自动编号
    record_id                 INTEGER NOT NULL,             -- 病历编号
    formular                  TEXT DEFAULT '',              -- 方剂
    formular_count            UNSIGNED TINYINT DEFAULT 0,   -- 付数
    advice                    NVARCHAR(40) DEFAULT '',      -- 医嘱
    usage                     NVARCHAR(20) DEFAULT '',      -- 煎煮法
    other_tcm_treatment       TEXT DEFAULT '',              -- 其他中医治疗
    nursing                   NVARCHAR(100) DEFAULT '',     -- 调护
    wm_treatment              TEXT DEFAULT '',              -- 西医治疗
    created_at                TIMESTAMP DEFAULT (datetime('now', 'localtime')),
    updated_at                TIMESTAMP DEFAULT (datetime('now', 'localtime'))
);
