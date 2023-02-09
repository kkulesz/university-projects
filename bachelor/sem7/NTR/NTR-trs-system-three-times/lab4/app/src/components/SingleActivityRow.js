import React from 'react';
import { Link, useNavigate } from 'react-router-dom';
import { useGlobalState } from '../state';

import { deleteActivity } from '../dataSource/activitiesApi';

const SingleActivityRow = (params) => {
    const activity = params.activity
    const { loggedUser } = useGlobalState()
    const navigate = useNavigate();

    const handleDelete = () => {

        deleteActivity(activity.code, loggedUser)
        navigate('/activitiesDashboard');
    }

    return <div>
        {activity.code} - {activity.budget} -
        <Link to={"/displayActivity"} state={{ activity }}>
            show
        </Link> -
        <Link to={"/updateActivityForm"} state={{ activity }}>
            update
        </Link> -

        <input
            type="submit"
            value="delete"
            style={{ marginTop: '10px' }}
            onClick={handleDelete}
        />
    </div>;
}

export default SingleActivityRow;
