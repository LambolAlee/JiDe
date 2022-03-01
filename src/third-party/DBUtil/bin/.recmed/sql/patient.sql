<sqls namespace="Patient">
    <!--[1]-->
    <define id="table">info_patient</define>
    <!--[2]-->
    <define id="fields">
        id, patient_name, sex, flag, birthday, ethnicity, native_place, birth_place, career
    </define>
    <!--[3]-->
    <define id="fields-no-id">
        patient_name, sex, flag, birthday, ethnicity, native_place, birth_place, career
    </define>
    <!--[4]-->
    <define id="fields-no-id-placeholder">
        :patient_name, :sex, :flag, :birthday, :ethnicity, :native_place, :birth_place, :career
    </define>

    <sql id="findByPatientId">
        SELECT <include defineId="fields"/> FROM <include defineId="table"/> WHERE id=%1
    </sql>

    <sql id="findByPatientIndex">
        SELECT <include defineId="fields"/> FROM <include defineId="table"/>
        WHERE (patient_name=%1 and sex=%2 and flag=%3)
    </sql>

    <sql id="findIndexById">
        SELECT patient_name, sex, flag FROM <include defineId="table"/> WHERE id=%1
    </sql>

    <sql id="insert">
        INSERT INTO <include defineId="table"/> (<include defineId="fields-no-id"/>)
        VALUES (<include defineId="fields-no-id-placeholder"/>)
    </sql>

    <sql id="update">
    </sql>

    <sql id="delete">
        DELETE FROM <include defineId="table"/> WHERE id=%1
    </sql>
</sqls>
