import React from 'react'
import { getUser } from '../dataSource/usersApi'
import { useNavigate } from 'react-router-dom';

import { useGlobalState } from '../state'


const UsersList = (props) => {
    const { setUser } = useGlobalState()
    const navigate = useNavigate();

    const users = props.users
    const onClick = async (e) => {
        e.preventDefault()
        const login = e.target.value

        // const response = 
        await getUser(login)
        localStorage.setItem('loggedUser', login)
        setUser(login)
        navigate('/activitiesDashboard');
        // IF NOT navigate('TODO')
    };

    return (
        <div>
            <h1 className="display-4" style={{ marginBottom: '2rem' }}>
                Konrad Kulesza
            </h1>
            <div>
                <form>
                    {users.map((user) => {
                        return (
                            <input
                                type="button"
                                key={user.login}
                                value={user.login}
                                style={{ margin: '2px 3px' }}
                                onClick={onClick}
                            />
                        );
                    })}
                </form>
            </div>
        </div>
    );

}

export default UsersList;
