import React, { useState } from 'react';
import { createUser } from '../dataSource/usersApi';
import { useNavigate } from 'react-router-dom';

import { useGlobalState } from '../state'

const CreateUserForm = () => {
    const {setUser} = useGlobalState()
    const navigate = useNavigate();

    const [userLogin, setUserLogin] = useState('');
    const handleChange = (e) => setUserLogin(e.target.value);
    const handleSubmit = async (e) => {
        e.preventDefault()
        
        // const response = 
        await createUser(userLogin)
        
        //if success
        // localStorage.setItem('loggedUser', userLogin)
        setUser(userLogin)
        navigate('/activitiesDashboard');

        //if not
        //TODO
     }

    return (
        <div>
            <h4>Add new user</h4>
            <div>
                <form onSubmit={handleSubmit}>
                    <div>
                        <input
                            type="text"
                            value={userLogin}
                            name="registrationLogin"
                            // className="form-control"
                            style={{ marginTop: '10px' }}
                            onChange={handleChange}
                        />
                        <input
                            type="submit"
                            value="Register"
                            // className="btn btn-primary"
                            style={{ marginTop: '10px' }}
                        />
                    </div>
                </form>
            </div>
        </div>
    );


}

export default CreateUserForm;
