<sqls namespace="Record">
    <!--consts definition here-->
    <define id="table">info_record</define>
    <define id="fields">
        id, patient_id, parent_record, clinic_date, age, doctor_name, doctor_id, place
    </define>

    <!--sql sentences here-->
    <sql id="findByPatientId">
        SELECT <include defineId="fields"/> FROM <include defineId="table"/> WHERE patient_id=%1
    </sql>
</sqls>
