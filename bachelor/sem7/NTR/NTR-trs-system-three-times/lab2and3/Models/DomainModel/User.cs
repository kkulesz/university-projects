using System;
using System.ComponentModel.DataAnnotations;

namespace lab2and3.Models.DomainModel
{
    public record User
    {
        public Guid UserId { get; init; }
        [MaxLength(50)]
        public string Login { get; init; }

        public DateTime CreatedAt { get; init; } = DateTime.Now;
    }
}