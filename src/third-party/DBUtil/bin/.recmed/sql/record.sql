<sqls namespace="Record">
    <!--consts definition here-->
    <define id="dbname">info_record</define>
    <define id="fields">
        id, patient_id, is_reexam, parent_record, clinic_date, age, doctor_name, doctor_id, place
    </define>

    <!--sql sentences here-->
    <sql id="findByRecordId">
        SELECT <include defineId="fields"/> FROM <include defineId="dbname"/> WHERE id=%1;
    </sql>
    <sql id="findByPatientId">
        SELECT <include defineId="fields"/> FROM <include defineId="dbname"/> WHERE patient_id=%1;
    </sql>
</sqls>
